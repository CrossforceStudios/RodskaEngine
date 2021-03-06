#pragma once

#include "RHICommand.h"
#include "Camera/Camera.h"
#include "Shader.h"
#include "RodskaEngine/Core/EngineCore.h"

namespace RodskaEngine {
	class  RodskaRenderer {
	public:
		RODSKA_EAPI	static void BeginScene(Camera* camera);
		RODSKA_EAPI	static void EndScene();
		RODSKA_EAPI	static void OnWindowResize(uint32_t width, uint32_t height);

		RODSKA_EAPI	static void SubmitMesh(const Ref<VertexArray> vertexArray, const Ref<Shader> shader, const glm::mat4& transform = glm::mat4(1.0f));
		RODSKA_EAPI	static void SubmitParticles(const Ref<VertexArray> vertexArray,  const Ref<Shader> particleShader, const glm::mat4& transform = glm::mat4(1.0f));
		RODSKA_EAPI static void ToggleWireframe();
		RODSKA_EAPI	static void Init();

		RODSKA_EAPI	inline static RHIAPI::RHI GetRHI() {return RHIAPI::GetRHI();}
	private:
		static glm::mat4 ViewProjectionMatrix;
		static glm::mat4 ViewMatrix;
	};


}