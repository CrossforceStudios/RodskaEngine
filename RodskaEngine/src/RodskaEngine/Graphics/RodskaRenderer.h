#pragma once

#include "RHICommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"
#include "RodskaScene.h"

namespace RodskaEngine {
	
	class RodskaRenderer {
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void SubmitMesh(const VertexArrayPtr& vertexArray, const Ref<Shader> shader, const glm::mat4& transform = glm::mat4(1.0f));
		static void Init();

		inline static RHIAPI::RHI GetRHI() {
			return RHIAPI::GetRHI();
		}
	private:
		static RodskaScene* m_Scene;
	};


}