set "DIR=%~dp0"

C:\VulkanSDK\1.4.309.0\Bin\glslc.exe "%DIR%simple_shader.vert" -o "%DIR%simple_shader.vert.spv"
C:\VulkanSDK\1.4.309.0\Bin\glslc.exe "%DIR%simple_shader.frag" -o "%DIR%simple_shader.frag.spv"
C:\VulkanSDK\1.4.309.0\Bin\glslc.exe "%DIR%point_light.vert" -o "%DIR%point_light.vert.spv"
C:\VulkanSDK\1.4.309.0\Bin\glslc.exe "%DIR%point_light.frag" -o "%DIR%point_light.frag.spv"

pause