//////////////
// #INCLUDE //
//////////////  

// GLM:
//#define GLM_ENABLE_EXPERIMENTAL     // Silly requirement since 0.9.9
#define GLM_FORCE_CTOR_INIT         // Constructors no longer init to identity since 0.9.9
#include <glm/glm.hpp>
#include <glm/gtc/packing.hpp>

// C/C++:
//#include <iostream>
#include <iomanip>   
#include <fstream>
#include <limits.h>
#include "OvoReader.h"
#define OV_MAXNUMBEROFCHARS 256

// Macro for printing an OvMatrix4 to console:   
#define MAT2STR(f, m) f << "   Matrix  . . . :  \t" << m[0][0] << "\t" << m[1][0] << "\t" << m[2][0] << "\t" << m[3][0] << std::endl \
                           << "                    \t" << m[0][1] << "\t" << m[1][1] << "\t" << m[2][1] << "\t" << m[3][1] << std::endl \
                           << "                    \t" << m[0][2] << "\t" << m[1][2] << "\t" << m[2][2] << "\t" << m[3][2] << std::endl \
                           << "                    \t" << m[0][3] << "\t" << m[1][3] << "\t" << m[2][3] << "\t" << m[3][3] << std::endl 

// Stripped-down redefinition of OvObject (just for the chunk IDs):
class OvObject
{
public:
	enum class Type : int  ///< Type of entities
	{
		// Foundation types:
		OBJECT = 0,
		NODE,
		OBJECT2D,
		OBJECT3D,
		LIST,

		// Derived classes:
		BUFFER,
		SHADER,
		TEXTURE,
		FILTER,
		MATERIAL,
		FBO,
		QUAD,
		BOX,
		SKYBOX,
		FONT,
		CAMERA,
		LIGHT,
		BONE,
		MESH,	   // Keep them...
		SKINNED, // ...consecutive        
		INSTANCED,
		PIPELINE,
		EMITTER,

		// Animation type
		ANIM,

		// Physics related:
		PHYSICS,

		// Terminator:
		LAST,
	};
};

// Stripped-down redefinition of OvMesh (just for the subtypes):
class OvMesh
{
public:
	enum class Subtype : int ///< Kind of mesh
	{
		// Foundation types:
		DEFAULT = 0,
		NORMALMAPPED,
		TESSELLATED,

		// Terminator:
		LAST,
	};
};

// Stripped-down redefinition of OvLight (just for the subtypes):
class OvLight
{
public:
	enum class Subtype : int ///< Kind of light
	{
		// Foundation types:
		OMNI = 0,
		DIRECTIONAL,
		SPOT,

		// Terminator:
		LAST,
	};
};

//legge ovoFile e ritorna una lista di oggetti 

//ID temporaneamente commentati
std::vector<Object *> OvoReader::readOVOfile(const char *name)
{
	//list of parsed object
	std::vector<Object *> objects;
	//list of materials
	std::vector<Material *> allMaterials;
	// Check for retrieve vertex:
	const bool verbose = true;
	// Open file:
	FILE *dat = fopen(name, "rb");
	// Create file of property:
	std::ofstream f("../resources/propertyFile.txt");
	// Configure stream:
	std::cout.precision(2);  // 2 decimals are enough
	std::cout << std::fixed;      // Avoid scientific notation
	Node *root = nullptr;
	// Parse chunks:	
	unsigned int chunkId, chunkSize;
	while (true)
	{
		fread(&chunkId, sizeof(unsigned int), 1, dat);
		if (feof(dat))
			break;
		fread(&chunkSize, sizeof(unsigned int), 1, dat);
		f << "[chunk id: " << chunkId << ", chunk size: " << chunkSize << ", chunk type: ";
		// Load whole chunk into memory:
		char *data = new char[chunkSize];
		if (fread(data, sizeof(char), chunkSize, dat) != chunkSize)
		{
			f << "ERROR: unable to read from file '" << name << "'" << std::endl;
			fclose(dat);
			delete[] data;
		}
		// Parse chunk information according to its type:
		unsigned int position = 0;
		switch ((OvObject::Type) chunkId)
		{
			///////////////////////////////
		case OvObject::Type::OBJECT: //
		{
			f << "version]" << std::endl;
			// OVO revision number:
			unsigned int versionId;
			memcpy(&versionId, data + position, sizeof(unsigned int));
			f << "   Version . . . :  " << versionId << std::endl;
			position += sizeof(unsigned int);
		}
		break;
		/////////////////////////////
		case OvObject::Type::NODE: //
		{
			f << "node]" << std::endl;
			// Node name:
			char nodeName[FILENAME_MAX];
			strcpy_s(nodeName, data + position);
			f << "   Name  . . . . :  " << nodeName << std::endl;
			position += (unsigned int)strlen(nodeName) + 1;
			// Node matrix:
			glm::mat4 matrix;
			memcpy(&matrix, data + position, sizeof(glm::mat4));
			if (verbose)
				MAT2STR(f, matrix);
			position += sizeof(glm::mat4);
			// Nr. of children nodes:
			unsigned int children;
			memcpy(&children, data + position, sizeof(unsigned int));
			f << "   Nr. children  :  " << children << std::endl;
			position += sizeof(unsigned int);
			// Optional target node, [none] if not used:
			char targetName[FILENAME_MAX];
			strcpy_s(targetName, data + position);
			f << "   Target node . :  " << targetName << std::endl;
			position += (unsigned int)strlen(targetName) + 1;

			root = new Node();
			root->setChildrenSize(children);
			root->setType(Object::Type::NODE);
			root->setName(nodeName);
			root->setID(root->getID());
				//idCounter++;
			root->setMatrix(matrix);

			objects.push_back(root);
		}
		break;
		/////////////////////////////////
		case OvObject::Type::MATERIAL: //
		{
			f << "material]" << std::endl;
			// Material name:
			char materialName[FILENAME_MAX];
			strcpy_s(materialName, data + position);
			f << "   Name  . . . . :  " << materialName << std::endl;
			position += (unsigned int)strlen(materialName) + 1;
			// Material term colors, starting with emissive:
			glm::vec3 emission, albedo;
			memcpy(&emission, data + position, sizeof(glm::vec3));
			f << "   Emission  . . :  " << emission.r << ", " << emission.g << ", " << emission.b << std::endl;
			position += sizeof(glm::vec3);
			// Albedo:
			memcpy(&albedo, data + position, sizeof(glm::vec3));
			f << "   Albedo  . . . :  " << albedo.r << ", " << albedo.g << ", " << albedo.b << std::endl;
			position += sizeof(glm::vec3);
			// Roughness factor:
			float roughness;
			memcpy(&roughness, data + position, sizeof(float));
			f << "   Roughness . . :  " << roughness << std::endl;
			position += sizeof(float);
			// Metalness factor:
			float metalness;
			memcpy(&metalness, data + position, sizeof(float));
			f << "   Metalness . . :  " << metalness << std::endl;
			position += sizeof(float);
			// Transparency factor:
			float alpha;
			memcpy(&alpha, data + position, sizeof(float));
			f << "   Transparency  :  " << alpha << std::endl;
			position += sizeof(float);
			// Albedo texture filename, or [none] if not used:
			char textureName[FILENAME_MAX];
			strcpy_s(textureName, data + position);
			f << "   Albedo tex. . :  " << textureName << std::endl;
			position += (unsigned int)strlen(textureName) + 1;
			// Normal map filename, or [none] if not used:
			char normalMapName[FILENAME_MAX];
			strcpy_s(normalMapName, data + position);
			f << "   Normalmap tex.:  " << normalMapName << std::endl;
			position += (unsigned int)strlen(normalMapName) + 1;
			// Height map filename, or [none] if not used:
			char heightMapName[FILENAME_MAX];
			strcpy_s(heightMapName, data + position);
			f << "   Heightmap tex.:  " << heightMapName << std::endl;
			position += (unsigned int)strlen(heightMapName) + 1;
			// Roughness map filename, or [none] if not used:
			char roughnessMapName[FILENAME_MAX];
			strcpy_s(roughnessMapName, data + position);
			f << "   Roughness tex.:  " << roughnessMapName << std::endl;
			position += (unsigned int)strlen(roughnessMapName) + 1;
			// Metalness map filename, or [none] if not used:
			char metalnessMapName[FILENAME_MAX];
			strcpy_s(metalnessMapName, data + position);
			f << "   Metalness tex.:  " << metalnessMapName << std::endl;
			position += (unsigned int)strlen(metalnessMapName) + 1;

			Material *material = new Material();
			material->setShininess((1 - (float)sqrt((int)roughness)) * 128);
			material->setName(materialName);
			material->setTexture(textureName);
			material->setAmbient(albedo*0.2f);
			material->setSpecular(albedo*0.4f);
			material->setDiffuse(albedo*0.6f);
			allMaterials.push_back(material);
		}
		break;
		////////////////////////////////
		case OvObject::Type::MESH:    //
		case OvObject::Type::SKINNED:
		{
			// Both standard and skinned meshes are handled through this case:
			bool isSkinned = false;
			if ((OvObject::Type) chunkId == OvObject::Type::SKINNED)
			{
				isSkinned = true;
				f << "skinned mesh]" << std::endl;
			}
			else
				f << "mesh]" << std::endl;
			// Mesh name:
			char meshName[FILENAME_MAX];
			strcpy_s(meshName, data + position);
			position += (unsigned int)strlen(meshName) + 1;
			f << "   Name  . . . . :  " << meshName << std::endl;
			//////////Mesh instance/////////
			//------ array of vertexRender order-------//
			std::vector<unsigned int> facesArray;
			// Mesh matrix:
			glm::mat4 matrix;
			memcpy(&matrix, data + position, sizeof(glm::mat4));
			if (verbose)
				MAT2STR(f, matrix);
			position += sizeof(glm::mat4);
			// Mesh nr. of children nodes:
			unsigned int children;
			memcpy(&children, data + position, sizeof(unsigned int));
			f << "   Nr. children  :  " << children << std::endl;
			position += sizeof(unsigned int);
			std::cout << "children of " << meshName << ": " << children << std::endl;
			// Optional target node, or [none] if not used:
			char targetName[FILENAME_MAX];
			strcpy_s(targetName, data + position);
			f << "   Target node . :  " << targetName << std::endl;
			position += (unsigned int)strlen(targetName) + 1;
			// Mesh subtype (see OvMesh SUBTYPE enum):
			unsigned char subtype;
			memcpy(&subtype, data + position, sizeof(unsigned char));
			char subtypeName[FILENAME_MAX];
			switch ((OvMesh::Subtype) subtype)
			{
			case OvMesh::Subtype::DEFAULT: strcpy_s(subtypeName, "standard"); break;
			case OvMesh::Subtype::NORMALMAPPED: strcpy_s(subtypeName, "normal-mapped"); break;
			case OvMesh::Subtype::TESSELLATED: strcpy_s(subtypeName, "tessellated"); break;
			default: strcpy_s(subtypeName, "UNDEFINED");
			}
			f << "   Subtype . . . :  " << (int)subtype << " (" << subtypeName << ")" << std::endl;
			position += sizeof(unsigned char);
			// Nr. of vertices:
			unsigned int vertices, faces;
			memcpy(&vertices, data + position, sizeof(unsigned int));
			f << "   Nr. vertices  :  " << vertices << std::endl;
			position += sizeof(unsigned int);
			// ...and faces:
			memcpy(&faces, data + position, sizeof(unsigned int));
			f << "   Nr. faces . . :  " << faces << std::endl;
			position += sizeof(unsigned int);
			// Material name, or [none] if not used:
			char materialName[FILENAME_MAX];
			strcpy_s(materialName, data + position);
			f << "   Material  . . :  " << materialName << std::endl;
			position += (unsigned int)strlen(materialName) + 1;
			// Mesh bounding sphere radius:
			float radius;
			memcpy(&radius, data + position, sizeof(float));
			f << "   Radius  . . . :  " << radius << std::endl;
			position += sizeof(float);

			// Mesh bounding box minimum corner:
			glm::vec3 bBoxMin;
			memcpy(&bBoxMin, data + position, sizeof(glm::vec3));
			f << "   BBox minimum  :  " << bBoxMin.x << ", " << bBoxMin.y << ", " << bBoxMin.z << std::endl;
			position += sizeof(glm::vec3);

			// Mesh bounding box maximum corner:
			glm::vec3 bBoxMax;
			memcpy(&bBoxMax, data + position, sizeof(glm::vec3));
			f << "   BBox maximum  :  " << bBoxMax.x << ", " << bBoxMax.y << ", " << bBoxMax.z << std::endl;
			position += sizeof(glm::vec3);

			// Optional physics properties:
			unsigned char hasPhysics;
			memcpy(&hasPhysics, data + position, sizeof(unsigned char));
			f << "   Physics . . . :  " << (int)hasPhysics << std::endl;
			position += sizeof(unsigned char);
			if (hasPhysics)
			{
				/**
				 * Mesh physics properties.
				 */

				struct PhysProps
				{
					// Pay attention to 16 byte alignement (use padding):      
					unsigned char type;
					unsigned char contCollisionDetection;
					unsigned char collideWithRBodies;
					unsigned char hullType;
					// Vector data:
					glm::vec3 massCenter;
					// Mesh properties:
					float mass;
					float staticFriction;
					float dynamicFriction;
					float bounciness;
					float linearDamping;
					float angularDamping;
					void *physObj;
				};

				PhysProps mp;
				memcpy(&mp, data + position, sizeof(PhysProps));
				position += sizeof(PhysProps);
				f << "      Type . . . :  " << (int)mp.type << std::endl;
				f << "      Hull type  :  " << (int)mp.hullType << std::endl;
				f << "      Cont. coll.:  " << (int)mp.contCollisionDetection << std::endl;
				f << "      Col. bodies:  " << (int)mp.collideWithRBodies << std::endl;
				f << "      Center . . :  " << mp.massCenter.x << ", " << mp.massCenter.y << ", " << mp.massCenter.z << std::endl;
				f << "      Mass . . . :  " << mp.mass << std::endl;
				f << "      Static . . :  " << mp.staticFriction << std::endl;
				f << "      Dynamic  . :  " << mp.dynamicFriction << std::endl;
				f << "      Bounciness :  " << mp.bounciness << std::endl;
				f << "      Linear . . :  " << mp.linearDamping << std::endl;
				f << "      Angular  . :  " << mp.angularDamping << std::endl;
			}
			// Extra information for skinned meshes:
			if (isSkinned)
			{
				// Initial mesh pose matrix:               
				glm::mat4 poseMatrix;
				memcpy(&poseMatrix, data + position, sizeof(glm::mat4));
				if (verbose)
					MAT2STR(f, poseMatrix);
				position += sizeof(glm::vec4);

				// Bone list:
				unsigned int nrOfBones;
				memcpy(&nrOfBones, data + position, sizeof(unsigned int));
				f << "   Nr. bones . . :  " << nrOfBones << std::endl;
				position += sizeof(unsigned int);

				for (unsigned int c = 0; c < nrOfBones; c++)
				{
					// Bone name:
					char boneName[FILENAME_MAX];
					strcpy_s(boneName, data + position);
					f << "      Bone name  :  " << boneName << " (" << c << ")" << std::endl;
					position += (unsigned int)strlen(boneName) + 1;

					// Initial bone pose matrix (already inverted):
					glm::mat4 boneMatrix;
					memcpy(&boneMatrix, data + position, sizeof(glm::mat4));
					if (verbose)
						MAT2STR(f, boneMatrix);
					position += sizeof(glm::mat4);
				}

				// Per vertex bone weights and indexes:               
				for (unsigned int c = 0; c < vertices; c++)
				{
					if (verbose)
						f << "   Bone data . . :  v" << c << std::endl;

					// Bone indexes:
					unsigned int boneIndex[4];
					memcpy(boneIndex, data + position, sizeof(unsigned int) * 4);
					if (verbose)
						f << "      index  . . :  " << boneIndex[0] << ", " << boneIndex[1] << ", " << boneIndex[2] << ", " << boneIndex[3] << std::endl;
					position += sizeof(unsigned int) * 4;

					// Bone weights:
					unsigned short boneWeightData[4];
					memcpy(boneWeightData, data + position, sizeof(unsigned short) * 4);
					if (verbose)
					{
						glm::vec4 boneWeight;
						boneWeight.x = glm::unpackHalf1x16(boneWeightData[0]);
						boneWeight.y = glm::unpackHalf1x16(boneWeightData[1]);
						boneWeight.z = glm::unpackHalf1x16(boneWeightData[2]);
						boneWeight.w = glm::unpackHalf1x16(boneWeightData[3]);
						f << "      weight . . :  " << boneWeight.x << ", " << boneWeight.y << ", " << boneWeight.z << ", " << boneWeight.w << std::endl;
					}
					position += sizeof(unsigned short) * 4;
				}
			}
			//TODO	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			float* meshVertices = new float[vertices * 3];
			float* meshTextures = new float[vertices * 2];
			float* meshNormals = new float[vertices * 3];
			//SETTO VERTICI TEXTURE E NORMALI
			// Interleaved and compressed vertex/normal/UV/tangent data:
			for (unsigned int c = 0; c < vertices; c++)
			{
				// Vertex coords:
				glm::vec3 vertex;
				std::memcpy(&vertex, data + position, sizeof(glm::vec3));
				position += sizeof(glm::vec3);

				// Vertex normal:
				unsigned int normalData;
				std::memcpy(&normalData, data + position, sizeof(unsigned int));
				position += sizeof(unsigned int);
				glm::vec4 normal = glm::unpackSnorm3x10_1x2(normalData);
				// Texture coordinates:
				unsigned short textureData[2];
				std::memcpy(textureData, data + position, sizeof(unsigned short) * 2);
				position += sizeof(unsigned short) * 2;

				glm::vec2 uv;
				uv.x = glm::unpackHalf1x16(textureData[0]);
				uv.y = glm::unpackHalf1x16(textureData[1]);
				// Tangent vector:
				unsigned int tangentData;
				std::memcpy(&tangentData, data + position, sizeof(unsigned int));
				position += sizeof(unsigned int);

				//meshVertex.push_back(new Vertex(vertex, glm::unpackSnorm3x10_1x2(normalData), textureDataVector));

				meshVertices[c * 3] = vertex.x;
				meshVertices[c * 3 + 1] = vertex.y;
				meshVertices[c * 3 + 2] = vertex.z;

				meshNormals[c * 3] = normal.x;
				meshNormals[c * 3 + 1] = normal.y;
				meshNormals[c * 3 + 2] = normal.z;

				meshTextures[c * 2] = uv.x;
				meshTextures[c * 2 + 1] = 1 - uv.y;
			}
			//setto gli indice delle facce
			unsigned int* indices = new unsigned int[faces * 3];
			unsigned int face[3];
			for (unsigned int c = 0; c < faces; c++)
			{
				// Face indexes:
				if (verbose) {
					f << "   Face data . . :  f" << c << " (" << face[0] << ", " << face[1] << ", " << face[2] << ")" << std::endl;
					//capire se posso spostarli fuori dal for
					memcpy(face, data + position, sizeof(unsigned int) * 3);
					position += sizeof(unsigned int) * 3;

					indices[c * 3] = face[0];
					indices[c * 3 + 1] = face[1];
					indices[c * 3 + 2] = face[2];
					/*		facesArray.push_back(face[0]);
							facesArray.push_back(face[1]);
							facesArray.push_back(face[2]);*/
				}
			}
			//////////////////////////////////////////////////////////////		
			//Creo la mesh
			Mesh *mesh = new Mesh();
			mesh->setName(meshName);
			mesh->setID(mesh->getID());
			//idCounter++;
			mesh->setMatrix(matrix);
			Material *material = nullptr;
			for (std::vector<Material*>::iterator it = allMaterials.begin(); it != allMaterials.end(); ++it)
			{
				if ((*it)->getName().compare(materialName) == 0)
					material = *it;
			}
			mesh->setMaterial(material);
			mesh->setRadius(radius);
			mesh->setNumberOfFaces(faces);
			mesh->setMatrix(matrix);
			mesh->setChildrenSize(children);
			mesh->generateVAO(meshVertices, meshNormals, meshTextures, indices, vertices);
			objects.push_back(mesh);
		}
		break;
		//////////////////////////////
		case OvObject::Type::LIGHT: //
		{
			f << "light]" << std::endl;
			// Light name:
			char lightName[FILENAME_MAX];
			strcpy_s(lightName, data + position);
			f << "   Name  . . . . :  " << lightName << std::endl;
			position += (unsigned int)strlen(lightName) + 1;

			// Light matrix:
			glm::mat4 matrix;
			memcpy(&matrix, data + position, sizeof(glm::mat4));
			if (verbose)
				MAT2STR(f, matrix);
			position += sizeof(glm::mat4);

			// Nr. of children nodes:
			unsigned int children;
			memcpy(&children, data + position, sizeof(unsigned int));
			f << "   Nr. children  :  " << children << std::endl;
			position += sizeof(unsigned int);

			// Optional target node name, or [none] if not used:
			char targetName[FILENAME_MAX];
			strcpy_s(targetName, data + position);
			f << "   Target node . :  " << targetName << std::endl;
			position += (unsigned int)strlen(targetName) + 1;

			// Light subtype (see OvLight SUBTYPE enum):
			unsigned char subtype;
			memcpy(&subtype, data + position, sizeof(unsigned char));
			char subtypeName[FILENAME_MAX];
			f << "   Subtype . . . :  " << (int)subtype << " (" << subtypeName << ")" << std::endl;
			position += sizeof(unsigned char);

			// Light color:
			glm::vec3 color;
			memcpy(&color, data + position, sizeof(glm::vec3));
			f << "   Color . . . . :  " << color.r << ", " << color.g << ", " << color.b << std::endl;
			position += sizeof(glm::vec3);

			// Influence radius:
			float radius;
			memcpy(&radius, data + position, sizeof(float));
			f << "   Radius  . . . :  " << radius << std::endl;
			position += sizeof(float);

			// Direction:
			glm::vec3 direction;
			memcpy(&direction, data + position, sizeof(glm::vec3));
			f << "   Direction . . :  " << direction.r << ", " << direction.g << ", " << direction.b << std::endl;
			position += sizeof(glm::vec3);

			// Cutoff:
			float cutoff;
			memcpy(&cutoff, data + position, sizeof(float));
			f << "   Cutoff  . . . :  " << cutoff << std::endl;
			position += sizeof(float);

			// Exponent:
			float spotExponent;
			memcpy(&spotExponent, data + position, sizeof(float));
			f << "   Spot exponent :  " << spotExponent << std::endl;
			position += sizeof(float);

			// Cast shadow flag:
			unsigned char castShadows;
			memcpy(&castShadows, data + position, sizeof(unsigned char));
			f << "   Cast shadows  :  " << (int)castShadows << std::endl;
			position += sizeof(unsigned char);

			// Volumetric lighting flag:
			unsigned char isVolumetric;
			memcpy(&isVolumetric, data + position, sizeof(unsigned char));
			f << "   Volumetric  . :  " << (int)isVolumetric << std::endl;
			position += sizeof(unsigned char);
			//////////////////////////////////////////////////////////////////////////////////////////7
			Light *light = new Light();
			light->setName(lightName);
			switch ((OvLight::Subtype) subtype)
			{
			case OvLight::Subtype::DIRECTIONAL: strcpy_s(subtypeName, "directional");
				light->setSubType(Light::SubType::DIRECTIONAL);
				break;
			case OvLight::Subtype::OMNI: strcpy_s(subtypeName, "omni");
				light->setSubType(Light::SubType::OMNI);
				break;
			case OvLight::Subtype::SPOT: strcpy_s(subtypeName, "spot");
				light->setSubType(Light::SubType::SPOTLIGHT);
				break;
			default:
				strcpy_s(subtypeName, "UNDEFINED");
				break;
			}
			//TODO dovrebbero essere 0,1,2,3, credo resettare id
			light->setID(light->getID());
			light->setMatrix(matrix);
			light->setColor(color);
			light->setDirection(direction);
			light->setCutoff(cutoff);
			light->setChildrenSize(children);
			objects.push_back(light);
		}
		break;
		//TODO credo si possa rimuovere
		/////////////////////////////
		case OvObject::Type::BONE: //
		{
			f << "bone]" << std::endl;

			// Bone name:
			char boneName[FILENAME_MAX];
			strcpy_s(boneName, data + position);
			f << "   Name  . . . . :  " << boneName << std::endl;
			position += (unsigned int)strlen(boneName) + 1;

			// Bone matrix:
			glm::mat4 matrix;
			memcpy(&matrix, data + position, sizeof(glm::mat4));
			if (verbose)
				MAT2STR(f, matrix);
			position += sizeof(glm::mat4);

			// Nr. of children nodes:
			unsigned int children;
			memcpy(&children, data + position, sizeof(unsigned int));
			f << "   Nr. children  :  " << children << std::endl;
			position += sizeof(unsigned int);

			// Optional target node, or [none] if not used:
			char targetName[FILENAME_MAX];
			strcpy_s(targetName, data + position);
			f << "   Target node . :  " << targetName << std::endl;
			position += (unsigned int)strlen(targetName) + 1;

			// Mesh bounding box minimum corner:
			glm::vec3 bBoxMin;
			memcpy(&bBoxMin, data + position, sizeof(glm::vec3));
			f << "   BBox minimum  :  " << bBoxMin.x << ", " << bBoxMin.y << ", " << bBoxMin.z << std::endl;
			position += sizeof(glm::vec3);

			// Mesh bounding box maximum corner:
			glm::vec3 bBoxMax;
			memcpy(&bBoxMax, data + position, sizeof(glm::vec3));
			f << "   BBox maximum  :  " << bBoxMax.x << ", " << bBoxMax.y << ", " << bBoxMax.z << std::endl;
			position += sizeof(glm::vec3);
		}
		break;
		///////////
		default: //
			f << "UNKNOWN]" << std::endl;
			f << "ERROR: corrupted or bad data in file " << name << std::endl;
			fclose(dat);
			delete[] data;
		}
		// Release chunk memory:
		delete[] data;
	}
	// Done:
	fclose(dat);
	std::cout << "\nFile parsed" << std::endl;
	return objects;
}
/*
void OvoReader::readChildren(FILE* dat, Node* root)
{
	case OvObject::Type::LIGHT:
	{
		light->setID(counterLightId);
		counterLightId++;
		idCounter++;
		light->setColor(glm::vec4(color.r, color.g, color.b, 1.f));
		light->setDirection(glm::vec4(direction.r, direction.g, direction.b, 1.f));
	}
}

Node*  OvoReader::readOVOfile2(const char *name) {

			case OvObject::Type::MATERIAL :
			{
				// Material term colors, starting with emissive:
				glm::vec3  emission, ambient, diffuse, specular;
				std::memcpy(&emission, data + position, sizeof(glm::vec3));
				std::cout << "   Emission  . . :  " << emission.r << ", " << emission.g << ", " << emission.b << std::endl;
				position += sizeof(glm::vec3);

				// Ambient:
				std::memcpy(&ambient, data + position, sizeof(glm::vec3));
				std::cout << "   Ambient . . . :  " << ambient.r << ", " << ambient.g << ", " << ambient.b << std::endl;
				position += sizeof(glm::vec3);

				// Diffuse:
				std::memcpy(&diffuse, data + position, sizeof(glm::vec3));
				std::cout << "   Diffuse . . . :  " << diffuse.r << ", " << diffuse.g << ", " << diffuse.b << std::endl;
				position += sizeof(glm::vec3);

				// Specular:
				std::memcpy(&specular, data + position, sizeof(glm::vec3));
				std::cout << "   Specular  . . :  " << specular.r << ", " << specular.g << ", " << specular.b << std::endl;
				position += sizeof(glm::vec3);

				// Shininess factor:
				float shininess;
				std::memcpy(&shininess, data + position, sizeof(float));
				std::cout << "   Shininess . . :  " << shininess << std::endl;
				position += sizeof(float);

				// Diffuse texture filename, or [none] if not used:
				char textureName[OV_MAXNUMBEROFCHARS];
				std::strcpy(textureName, data + position);
				std::cout << "   Diffuse tex.  :  " << textureName << std::endl;
				position += (unsigned int)strlen(textureName) + 1;

				Material* material = new Material();
				if (alpha != 1)
				{
					material->activeTransparencies();
				}
								material->setName(materialName);
								material->setID(idCounter);
								idCounter++;
								//material->setAlpha(alpha);
								material->setShininess(shininess);
								material->setAmbient(glm::vec4(ambient.r, ambient.g, ambient.b, 1.f));
								material->setDiffuse(glm::vec4(diffuse.r, diffuse.g, diffuse.b, 1.f));
								material->setSpecular(glm::vec4(specular.r, specular.g, specular.b, 1.f));
								if (textureName != "[none]")
								{
									Texture* texture = new Texture(textureName);
									material->setTexture(texture);
								}

					}*/

