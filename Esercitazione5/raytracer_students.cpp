#include "raytracer.h"
#include "material.h"
#include "vectors.h"
#include "argparser.h"
#include "raytree.h"
#include "utils.h"
#include "mesh.h"
#include "face.h"
#include "sphere.h"

// casts a single ray through the scene geometry and finds the closest hit
bool
RayTracer::CastRay (Ray & ray, Hit & h, bool use_sphere_patches) const
{
	bool answer = false;
	Hit nearest = Hit();

	// intersect each of the quads
	for (int i = 0; i < mesh->numQuadFaces (); i++)
	{
		Face *f = mesh->getFace (i);
		if (f->intersect (ray, h, args->intersect_backfacing))
			if( h.getT() < nearest.getT() )
			{
				answer = true;
				nearest = h;
			}
	}

	// intersect each of the spheres (either the patches, or the original spheres)
	if (use_sphere_patches){
		for (int i = mesh->numQuadFaces (); i < mesh->numFaces (); i++){
			Face *f = mesh->getFace (i);
			if (f->intersect (ray, h, args->intersect_backfacing))
				if( h.getT() < nearest.getT() ){
					answer = true;
					nearest = h;
				}
		}
	}
	else{
		const vector < Sphere * >&spheres = mesh->getSpheres ();
		for (unsigned int i = 0; i < spheres.size (); i++)		{
			if (spheres[i]->intersect (ray, h))
				if( h.getT() < nearest.getT() )
				{
					answer = true;
					nearest = h;
				}
		}
	}

  h = nearest;
  return answer;
}

Vec3f
RayTracer::TraceRay (Ray & ray, Hit & hit, int bounce_count) const
{
	// false per hard shadow
	// true per soft shadow 
	bool softShadow = true;
	// numero di raggi per luci ad area
	const int NUM_RAY_TO_LIGHT = 64;

	hit = Hit ();
	bool intersect = CastRay (ray, hit, false);

	if( bounce_count == args->num_bounces )
	RayTree::SetMainSegment (ray, 0, hit.getT () );
	else
	RayTree::AddReflectedSegment(ray, 0, hit.getT() );

	Vec3f answer = args->background_color;

	Material *m = hit.getMaterial ();
	if (intersect == true)
	{

		assert (m != NULL);
		Vec3f normal = hit.getNormal ();
		// punto dell'oggetto colpito
		Vec3f point = ray.pointAtParameter (hit.getT ());

		// ----------------------------------------------
		// ambient light
		answer = args->ambient_light * m->getDiffuseColor ();

		// ----------------------------------------------
		// if the surface is shiny...
		Vec3f reflectiveColor = m->getReflectiveColor ();

		// ==========================================
		// ASSIGNMENT:  ADD REFLECTIVE LOGIC
		// ==========================================
	
		// se (il punto sulla superficie e' riflettente & bounce_count>0)
		/* per vedere se è è riflettente guardo se la lunghezza del vettore è > 0
		(almeno una componente diversa da 0)*/
		if (reflectiveColor.Length() > 0 && bounce_count > 0) {
			// calcolare ReflectionRay  R=2(normal,l)n - l
			Vec3f rayVector = ray.getDirection();
			Vec3f reflection = rayVector - (2 * rayVector.Dot3(normal) * normal);
			reflection.Normalize();
			Ray* newRay = new Ray(point, reflection);
			//	invocare TraceRay(ReflectionRay, hit,bounce_count-1)
			// aggiungere ad answer il contributo riflesso [moltiplicare per k_r]
			answer += TraceRay(*newRay, hit, bounce_count - 1) * reflectiveColor;
		}

		// ----------------------------------------------
		// add each light
		int num_lights = mesh->getLights ().size ();
		for (int i = 0; i < num_lights; i++)
		{
			// ==========================================
			// ASSIGNMENT:  ADD SHADOW LOGIC
			// ==========================================

			if (softShadow == false) {
				/*========================================
					HARD SHADOWN
				=========================================*/

				Face* f = mesh->getLights()[i];
				Vec3f pointOnLight = f->computeCentroid();
				Vec3f dirToLight = pointOnLight - point;
				dirToLight.Normalize();

				// creare shadow ray verso il punto luce, dal punto colpito
				Ray* shadowRay = new Ray(point, dirToLight);
				// controllare il primo oggetto colpito da tale raggio e verificare se è una luce
				Hit* hitShadow = new Hit();
				bool colpito = CastRay(*shadowRay, *hitShadow, false);
				if (colpito) {
					Vec3f puntoColpito = shadowRay->pointAtParameter(hitShadow->getT());
					// distanza dal punto colpito al punto della luce
					float dist = (puntoColpito - pointOnLight).Length();
					// se ho colpito la luce la distanza deve essere 0
					if (dist < 0.01)
						if (normal.Dot3(dirToLight) > 0)
						{
							Vec3f lightColor = 0.2 * f->getMaterial()->getEmittedColor() * f->getArea();
							answer += m->Shade(ray, hit, dirToLight, lightColor, args);
						}
				}
			}else{
				/*======================================
					SOFT SHADOWN
				=======================================*/
				Face *f = mesh->getLights ()[i];

				int rowColumn = sqrt(NUM_RAY_TO_LIGHT);

				for (int rowIndex = 0; rowIndex < rowColumn; rowIndex++) {
					for (int columnIndex = 0; columnIndex < rowColumn; columnIndex++) {
						Vec3f pointOnLight = f->getPoint(static_cast<float>(rowIndex) / rowColumn, static_cast<float>(columnIndex) / rowColumn);
						Vec3f dirToLight = pointOnLight - point;
						dirToLight.Normalize();
						// creare shadow ray verso il punto luce, dal punto colpito
						Ray* shadowRay = new Ray(point, dirToLight);
						// controllare il primo oggetto colpito da tale raggio e verificare se è una luce
						Hit* hitShadow = new Hit();
						bool colpito = CastRay(*shadowRay, *hitShadow, false);
						if (colpito) {
							Vec3f puntoColpito = shadowRay->pointAtParameter(hitShadow->getT());
							// distanza dal punto colpito al punto della luce
							float dist = (puntoColpito - pointOnLight).Length();
							// se ho colpito la luce la distanza deve essere 0
							if (dist < 0.01)
								if (normal.Dot3(dirToLight) > 0)
								{
									Vec3f lightColor = 0.2 * f->getMaterial()->getEmittedColor() * (f->getArea() / (rowColumn * rowColumn));
									answer += m->Shade(ray, hit, dirToLight, lightColor, args);
								}
						}
					}
				}
			}
		} // fine for
	}
	return answer;
}