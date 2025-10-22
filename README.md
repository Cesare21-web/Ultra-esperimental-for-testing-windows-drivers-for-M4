# Ultra-esperimental-for-testing-windows-drivers-for-M4

AGXStubDriver - KMDF stub driver (ARM64) for Apple AGX M4 (test)

Files included:
- AGXStub.c      : Source code for KMDF driver (stub)
- AGXStub.inf    : INF file to install the driver (uses fake hardware ID PCI\VEN_APPLE&DEV_AGXM4)
- README.txt     : This file

Instructions:
1) Create a new Kernel Mode Driver (KMDF) project in Visual Studio targeting ARM64.
2) Replace the generated driver source with AGXStub.c content.
3) Add AGXStub.inf to the project output directory.
4) Build the project for ARM64 (Release/Debug).
5) Create/sign a test certificate and enable test signing on Windows:
   - bcdedit /set testsigning on
   - reboot
6) Sign the driver (use signtool with your test cert) and install:
   - pnputil /add-driver AGXStub.inf /install
7) Check Event Viewer (System) and Kernel logs for KdPrint messages:
   - "AGXStubDriver: Driver loaded successfully"

Notes:
- This driver is a non-malicious stub; it does NOT access hardware MMIO.
- You are responsible for compiling and testing on your own Windows ARM machine.
- Do NOT attempt to load unsigned kernel drivers without proper test signing; it may prevent the system from booting into normal mode.
