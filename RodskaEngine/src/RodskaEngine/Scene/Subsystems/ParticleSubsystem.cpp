#include "rdskpch.h"

#include "ParticleSubsystem.h"
#include <Platform/OpenGL/OpenGLShader.h>
#include "RodskaEngine/Graphics/Buffer.h"
#include "RodskaEngine/Graphics/Particles/Emitters/FlowParticleEmitter.h"

namespace RodskaEngine {
	ParticleSubsystem::ParticleSubsystem(ShaderLibrary library_shader, Scene* scene) : m_Library(library_shader), m_Scene(scene)
	{

	}
	ParticleSubsystem::~ParticleSubsystem()
	{
	}
	void ParticleSubsystem::AddObject(RodskaObject& object)
	{
		auto& meshComponent = object.GetComponent<RDSK_COMP(Mesh)>();
		auto& particleComponent = object.GetComponent<RDSK_COMP(ParticleEmitter)>();
		auto mesh = Mesh::CreateFromObjFile("assets/models/particle_quad.obj", VertexType::PosAndTexCoord);
		mesh->SetVertexType(VertexType::PosAndTexCoord);
		mesh->SetMeshType(MeshType::Particle);
		mesh->SetupBuffers({ 
			{ RodskaEngine::ShaderDataType::Float3, "a_Position"},
			{ RodskaEngine::ShaderDataType::Float2, "a_TexCoord"}
		});
		mesh->SetupArray();
		mesh->SetShaderLibrary(m_Library);
		mesh->SetCurrentShader("Particle");
		Particle baseParticle = Particle(mesh, Texture2D::Create(particleComponent.ParticleFile, particleComponent.TextureKind,
			particleComponent.SizeY, particleComponent.SizeX), particleComponent.Lifetime, particleComponent.Speed, particleComponent.UpdateTime);
		FlowParticleEmitter* emitter = new FlowParticleEmitter(baseParticle, object.GetComponent<RDSK_COMP(Transform)>(), 
			particleComponent.MaxParticles, particleComponent.CreationPeriod);
		emitter->SetPositionRNDRange(particleComponent.Range);
		emitter->SetSpeedRNDRange(particleComponent.Range);
		emitter->SetScaleRNDRange(particleComponent.Range);
		m_Emitters.push_back(emitter);
		particleComponent.Emitter = emitter;
		m_Objects.push_back(object);
	}

	void ParticleSubsystem::OnUpdate(TimeStep ts)
	{
		for (auto& emitter : m_Emitters) {
			switch (RodskaRenderer::GetRHI()) {
			case RHIAPI::RHI::OpenGL:
				auto openGLShader = std::dynamic_pointer_cast<OpenGLShader>(m_Library.Get("Particle"));
				openGLShader->UploadUniformInt("texture_sampler", 0);
				break;
			}
			emitter->SetViewMatrix(m_Scene->mainCamera->GetViewMatrix());
			emitter->OnUpdateParticle(ts);
		}
	}
}