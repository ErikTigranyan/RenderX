#pragma once

#include "Camera.h"

// lib
#include <vulkan/vulkan.h>

namespace rex {
	struct FrameInfo {
		int frameIndex;
		float frameTime;
		VkCommandBuffer commandBuffer;
		Camera &camera;
		VkDescriptorSet globalDescriptorSet;
	};
} // namespace rex