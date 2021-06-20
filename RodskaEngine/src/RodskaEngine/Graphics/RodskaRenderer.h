#pragma once

#include "RHICommand.h"

namespace RodskaEngine {
	
	class RodskaRenderer {
	public:
		static void BeginScene();
		static void EndScene();

		static void SubmitMesh(const VertexArrayPtr& vertexArray);


		inline static RHIAPI::RHI GetRHI() {
			return s_RHI;
		}
	private:
		static RHIAPI::RHI s_RHI;

	};


}