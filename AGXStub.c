#include <ntddk.h>
#include <wdf.h>

DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD AGX_EvtDeviceAdd;
EVT_WDF_OBJECT_CONTEXT_CLEANUP AGX_EvtDriverContextCleanup;

typedef struct _DEVICE_CONTEXT {
    ULONG DummyValue;
} DEVICE_CONTEXT, *PDEVICE_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DEVICE_CONTEXT, DeviceGetContext);

NTSTATUS
DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
    WDF_DRIVER_CONFIG config;
    NTSTATUS status;

    WDF_DRIVER_CONFIG_INIT(&config, AGX_EvtDeviceAdd);
    config.EvtDriverUnload = NULL;

    KdPrint(("AGXStubDriver: Initializing driver\n"));

    status = WdfDriverCreate(DriverObject, RegistryPath, WDF_NO_OBJECT_ATTRIBUTES, &config, WDF_NO_HANDLE);
    if (!NT_SUCCESS(status)) {
        KdPrint(("AGXStubDriver: WdfDriverCreate failed (0x%x)\n", status));
        return status;
    }

    KdPrint(("AGXStubDriver: Driver loaded successfully\n"));
    return STATUS_SUCCESS;
}

NTSTATUS
AGX_EvtDeviceAdd(_In_ WDFDRIVER Driver, _Inout_ PWDFDEVICE_INIT DeviceInit)
{
    UNREFERENCED_PARAMETER(Driver);
    NTSTATUS status;
    WDFDEVICE device;
    PDEVICE_CONTEXT devContext;

    KdPrint(("AGXStubDriver: EvtDeviceAdd called\n"));

    status = WdfDeviceCreate(&DeviceInit, WDF_NO_OBJECT_ATTRIBUTES, &device);
    if (!NT_SUCCESS(status)) {
        KdPrint(("AGXStubDriver: WdfDeviceCreate failed (0x%x)\n", status));
        return status;
    }

    devContext = DeviceGetContext(device);
    devContext->DummyValue = 0xDEADBEEF;

    KdPrint(("AGXStubDriver: Device created successfully (DummyValue=0x%X)\n", devContext->DummyValue));
    return STATUS_SUCCESS;
}
