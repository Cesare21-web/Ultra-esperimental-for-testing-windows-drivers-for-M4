
## Additional helper files added
- AGXStub.vcxproj : minimal Visual Studio project for KMDF driver (ARM64) — may need adjustments in Visual Studio for driver type and WDK.
- build.ps1 : helper script to invoke MSBuild (run in Developer Command Prompt).
- sign_and_install.ps1 : helper to create a test cert and sign the driver (requires Administrator).
- .github/workflows/package.yml : GitHub Actions workflow that packages source files into an artifact (does NOT build the driver).

> Note: Building signed kernel drivers should be done on a trusted Windows machine with Visual Studio + WDK installed. The workflow intentionally **does not** attempt to compile the driver in CI to avoid unsafe or unreliable automation.
