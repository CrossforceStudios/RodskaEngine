#pragma once

#include <RodskaEngine/Core/EngineCore.h>
#include <RodskaEngine/Graphics/Objects/Mesh.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "ScriptableRodskaObject.h"
#include "RodskaEngine/Core/TimeStep.h"
#include <RodskaEngine/Graphics/Camera/Camera.h>
#include "RodskaEngine/UI/Editor/PropertyRegistry.h"
#include "imgui.h"
#include "RodskaEngine/Graphics/Texture.h"
#include "entt.hpp"

namespace RodskaEngine {
	class ScriptableRodskaObject;
	class FlowParticleEmitter;
	
	 RDSK_DEFCOMP(Transform) {

		  glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		  glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		  glm::vec3 Scale = { 0.1f, 0.1f, 0.1f };

		 RODSKA_EAPI RDSKComponent_Transform() = default;

		 RODSKA_EAPI RDSKComponent_Transform(const RDSK_COMP(Transform)& transformComponent) = default;
		 RODSKA_EAPI RDSKComponent_Transform(const glm::vec3& translation) : Translation(translation) {}

		 RODSKA_EAPI glm::mat4 GetTransform() const {
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation) * rotation * glm::scale(glm::mat4(1.0f), Scale);
		}

		 RODSKA_EAPI RDSKComponent_Transform(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale) : Translation(translation), Rotation(rotation), Scale(scale) {}
		 RODSKA_EAPI operator const glm::mat4& () const { return GetTransform(); }
		 RODSKA_EAPI operator glm::mat4& () { return GetTransform(); }

	};


	 RDSK_DEFCOMP(Mesh) {
		std::string MeshFile;
		bool IsParticle = false;
		std::string Shader;
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
		RODSKA_EAPI RDSKComponent_Mesh() = default;
		RODSKA_EAPI RDSKComponent_Mesh(const RDSK_COMP(Mesh)& other) = default;
		RODSKA_EAPI RDSKComponent_Mesh(const std::string& file, const std::string& newShader, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f }) : MeshFile(file), Color(color), Shader(newShader) {};
		RODSKA_EAPI bool operator ==(const RDSK_COMP(Mesh)& rhs) {
			return (MeshFile == rhs.MeshFile) && (Shader == rhs.Shader) && (Color == rhs.Color);
		}
	};

	 RDSK_DEFCOMP(Terrain) {
		 std::string Heightmap;
		 int MaxY;
		 int MinY;
		 std::string TextureFile;
		 int TextInc;
		 RODSKA_EAPI RDSKComponent_Terrain() = default;
		 RODSKA_EAPI RDSKComponent_Terrain(const RDSK_COMP(Terrain) & other) = default;
		 RODSKA_EAPI RDSKComponent_Terrain(const std::string & heightmap, int minY, int maxY, const std::string & texture, int textInc) : Heightmap(heightmap), MaxY(maxY), MinY(minY), TextureFile(texture), TextInc(textInc) {};
		 RODSKA_EAPI bool operator ==(const RDSK_COMP(Terrain) & rhs) {
			 return (Heightmap == rhs.Heightmap) && (MaxY == rhs.MaxY) && (MinY == rhs.MinY) && (TextureFile == rhs.TextureFile) && (TextInc == rhs.TextInc);
		 }
	 };

	 RDSK_DEFCOMP(Tag) {
	    std::string Tag;
		RODSKA_EAPI RDSKComponent_Tag() = default;
		RODSKA_EAPI RDSKComponent_Tag(const RDSK_COMP(Tag)& other) = default;
		RODSKA_EAPI RDSKComponent_Tag(const std::string& tag) : Tag(tag) {};
		RODSKA_EAPI void SetTag(const std::string& tag) {
			Tag = tag;
		}
	};

	 RDSK_DEFCOMP(Camera) {
		RodskaEngine::SceneCamera* Camera;
		bool FixedAspectRatio = false;
		bool Primary = false;
		RODSKA_EAPI RDSKComponent_Camera() = default;
		RODSKA_EAPI RDSKComponent_Camera(const RDSK_COMP(Camera)& other) = default;
		RODSKA_EAPI RDSKComponent_Camera(RodskaEngine::SceneCamera* camera) : Camera(camera) {}
	};

	 RDSK_DEFCOMP(Light) {
		glm::vec4 LightColor = { 0.0f, 0.75f, 0.5f, 1.0f };
		float Ambience = 0.1f;
		float ConstantAttenuation = 1;
		float LinearAttenuation = 0;
		float ExponentAttenuation = 0;
		glm::vec3 Position = { 0.0f, 0.0f, 1.0f };

		RODSKA_EAPI RDSKComponent_Light() = default;
		RODSKA_EAPI RDSKComponent_Light(const RDSK_COMP(Light) & other) = default;
	};

	 RDSK_DEFCOMP(Material) {
		 glm::vec4 Diffuse = { 0.0f, 0.75f, 0.5f, 1.0f };
		 glm::vec4 Ambient = { 0.0f, 0.75f, 0.5f, 1.0f };
		 glm::vec4 Specular = { 0.0f, 0.75f, 0.5f, 1.0f };
		 bool UsesTexture = false;
		 float Reflectance = 0;

		 RODSKA_EAPI RDSKComponent_Material() = default;
		 RODSKA_EAPI RDSKComponent_Material(const RDSK_COMP(Material) & other) = default;
	 };

	 RDSK_DEFCOMP(NativeScript) {
		ScriptableRodskaObject* Object = nullptr;

		ScriptableRodskaObject*(*OnInstantiate)() ;
		void (*OnDestroy)(RDSK_COMP(NativeScript)*);

		template<typename T>
		RODSKA_EAPI void Bind() {
			OnInstantiate = []() { return static_cast<ScriptableRodskaObject*>(new T()); };
			OnDestroy = [](RDSK_COMP(NativeScript)*  nsc) { delete nsc->Object; nsc->Object = nullptr; };

		}
	};

	 RDSK_DEFCOMP(ParticleEmitter) {
		glm::vec3 Speed;
		float Range;
		float Lifetime;
		uint32_t MaxParticles;
		float CreationPeriod;
		FlowParticleEmitter* Emitter;
		bool Active;
		TextureType TextureKind = TextureType::Static;
		float SizeX = 1.0f;
		float SizeY = 1.0f;

		float UpdateTime = 0.2f;
		std::string ParticleFile;
		RDSKComponent_ParticleEmitter() = default;
		RDSKComponent_ParticleEmitter(const RDSK_COMP(ParticleEmitter) & other) = default;
	};

	 RDSK_DEFCOMP(UI) {
		 std::string UIFile;
		 std::string UIStylesheet;
		 RDSKComponent_UI() = default;
		 RDSKComponent_UI(const RDSK_COMP(UI) & other) = default;
	 };



	// Registers
	RODSKA_EAPI void RegisterAllBuiltinComponents();

}

