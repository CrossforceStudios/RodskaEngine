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

namespace RodskaEngine {
	class ScriptableRodskaObject;
	RDSK_DEFCOMP(Transform)

		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 0.1f, 0.1f, 0.1f };

		RDSKComponent_Transform() = default;

		RDSKComponent_Transform(const RDSK_COMP(Transform)& transformComponent) = default;
		RDSKComponent_Transform(const glm::vec3& translation) : Translation(translation) {}

		glm::mat4 GetTransform() const {
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation) * rotation * glm::scale(glm::mat4(1.0f), Scale);
		}

		RDSKComponent_Transform(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale) : Translation(translation), Rotation(rotation), Scale(scale) {}
		operator const glm::mat4& () const { return GetTransform(); }
		operator glm::mat4& () { return GetTransform(); }

	};


	RDSK_DEFCOMP(Mesh)
		std::string MeshFile;
		std::string Shader;
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
		RDSKComponent_Mesh() = default;
		RDSKComponent_Mesh(const RDSK_COMP(Mesh)& other) = default;
		RDSKComponent_Mesh(const std::string& file, const std::string& newShader, const glm::vec4& color = { 1.0f, 1.0f, 1.0f, 1.0f }) : MeshFile(file), Color(color), Shader(newShader) {};
		bool operator ==(const RDSK_COMP(Mesh)& rhs) {
			return (MeshFile == rhs.MeshFile) && (Shader == rhs.Shader) && (Color == rhs.Color);
		}
	};

	RDSK_DEFCOMP(Tag)
		std::string Tag;
		RDSKComponent_Tag() = default;
		RDSKComponent_Tag(const RDSK_COMP(Tag)& other) = default;
		RDSKComponent_Tag(const std::string& tag) : Tag(tag) {};
		void SetTag(const std::string& tag) {
			Tag = tag;
		}
	};

	RDSK_DEFCOMP(Camera)
		Ref<RodskaEngine::Camera> Camera;
		bool FixedAspectRatio = false;
		bool Primary = false;
		RDSKComponent_Camera() = default;
		RDSKComponent_Camera(const RDSK_COMP(Camera)& other) = default;
		RDSKComponent_Camera(const Ref<RodskaEngine::Camera>& camera) : Camera(camera) {}
	};

	RDSK_DEFCOMP(Light)
		glm::vec4 LightColor = { 0.0f, 0.75f, 0.5f, 1.0f };
		float Ambience = 0.1f;
		RDSKComponent_Light() = default;
		RDSKComponent_Light(const RDSK_COMP(Light) & other) = default;
	};


	RDSK_DEFCOMP(NativeScript)
		ScriptableRodskaObject* Object = nullptr;

		std::function<void()> InstantiateFunction;
		std::function<void()> DestroyInstanceFunction;
		std::function<void(ScriptableRodskaObject*)> OnCreateFunction;

		std::function<void(ScriptableRodskaObject*,TimeStep)> OnUpdateFunction;
		std::function<void(ScriptableRodskaObject*)> OnDestroyFunction;

		template<typename T>
		void Bind() {
			InstantiateFunction = [&Object]() { Object = new T() };
			DestroyInstanceFunction = [&Object]() { delete (*T)Instance; Instance = nullptr; };
			OnCreateFunction = [](ScriptableRodskaObject* instance) { ((T*)instance)->OnCreate(); }
			OnUpdateFunction = [](ScriptableRodskaObject* instance, TimeStep ts) { ((T*)instance)->OnUpdate(ts); }
			OnDestroyFunction = [](ScriptableRodskaObject* instance) { ((T*)instance)->OnDestroy(); }

		}
	};



	// Registers
	void RegisterAllBuiltinComponents();

}

