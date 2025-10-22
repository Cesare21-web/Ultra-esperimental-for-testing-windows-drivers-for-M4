Param(
    [string]$Configuration = "Release"
)

# Build the vcxproj using msbuild. Run this inside Visual Studio Developer Command Prompt or where MSBuild is available.
$proj = "AGXStub.vcxproj"
Write-Host "Building $proj Configuration=$Configuration Platform=ARM64"
& msbuild $proj /p:Configuration=$Configuration /p:Platform=ARM64 /m || exit $LASTEXITCODE
Write-Host "Build finished. Output should be in .\bin\$Configuration\"
