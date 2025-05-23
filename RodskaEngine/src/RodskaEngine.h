#pragma once

// For use by Rodska games and applications

#include "RodskaEngine/Core/RodskaApp.h"
#include "RodskaEngine/Core/AppLog.h"
#include "RodskaEngine/Core/Layer.h"
#include "RodskaEngine/Input/InputCodes.h"
#include "RodskaEngine/Input/InputComponent.h"
#include "RodskaEngine/UI/UICore/GUIBuilder.h"
#include "RodskaEngine/UI/Editor/DockBuilder.h"
#include "RodskaEngine/UI/Editor/EditorDock.h"
#include "RodskaEngine/UI/Editor/SceneViewport.h"
#include "RodskaEngine/UI/Editor/Panels/SceneHierarchyPanel.h"
#include "RodskaEngine/UI/Editor/Panels/IOPanel.h"

#include "RodskaEngine/UI/UILayer.h"

#include "RodskaEngine/Core/TimeStep.h"
// -- Graphics ----------------------------------
#include "RodskaEngine/Graphics/RodskaRenderer.h"
#include "RodskaEngine/Graphics/RHIAPI.h"
#include "RodskaEngine/Graphics/RHICommand.h"
#include "RodskaEngine/Graphics/Buffer.h"
#include "RodskaEngine/Graphics/Shader.h"
#include "RodskaEngine/Graphics/Texture.h"
#include "RodskaEngine/Graphics/Framebuffer.h"
#include "RodskaEngine/Graphics/VertexArray.h"
#include "RodskaEngine/Graphics/Camera/CameraCore.h"
#include "RodskaEngine/Graphics/Camera/OrthographicCamera.h"
#include "RodskaEngine/Graphics/Camera/SceneCamera.h"

#include "RodskaEngine/Graphics/UserData/Material.h"

#include "RodskaEngine/Graphics/Objects/Mesh.h"

#include "RodskaEngine/Graphics/Particles/ParticleEmitter.h"
#include "RodskaEngine/Graphics/Particles/Emitters/FlowParticleEmitter.h"
#include "RodskaEngine/Graphics/Objects/Particle.h"
// -- Graphics (UI) ---------------------------------------

#include "RodskaEngine/UI/UICore/ImGuiBackend.h"
// ----------------------------------------------

// -- Scene & Entities --------------------------

#include "RodskaEngine/Scene/Scene.h"
#include "RodskaEngine/Scene/BuiltinComponents.h"
#include "RodskaEngine/Scene/RodskaObject.h"
#include "RodskaEngine/Scene/Subsystems/MeshSystem.h"
#include "RodskaEngine/Scene/Subsystems/ParticleSubsystem.h"
#include "RodskaEngine/Scene/ScriptableRodskaObject.h"
#include "RodskaEngine/Scene/SceneSerializer.h"
// ----------------------------------------------

// -- Modules  --------------------------

#include "RodskaEngine/Core/PluginCore.h"
#include "RodskaEngine/Core/ModuleHandler.h"

// ----------------------------------------------