# This script will create a test signing certificate, sign AGXStub.sys and install the driver INF.
# Run as Administrator on the Windows machine where you will test the driver.
# Requires: MakeCert (or New-SelfSignedCertificate) and signtool.exe from Windows SDK.

$certName = "CN=AGXTestCert"
$cert = New-SelfSignedCertificate -Type CodeSigningCert -Subject $certName -CertStoreLocation "Cert:\LocalMachine\My"
Write-Host "Created test certificate:" $cert.Thumbprint

# Export PFX for signtool if needed (optional)
$pfxPath = "$env:TEMP\AGXTestCert.pfx"
$password = Read-Host -AsSecureString "Enter a password to protect the PFX (press enter to skip)"

if ($password.Length -gt 0) {
    Export-PfxCertificate -Cert "Cert:\LocalMachine\My\$($cert.Thumbprint)" -FilePath $pfxPath -Password $password
    Write-Host "Exported PFX to $pfxPath"
}

# Enable test signing and reboot (uncomment to enable)
#bcdedit /set testsigning on
#Write-Host "Test signing enabled. Reboot to take effect."

# Sign the driver with signtool (example, requires cert in store)
$sysPath = ".\bin\Release\AGXStub.sys"
if (Test-Path $sysPath) {
    Write-Host "Signing $sysPath"
    & signtool sign /fd SHA256 /a /n "AGXTestCert" $sysPath
    Write-Host "Signing complete."
} else {
    Write-Host "Driver binary not found at $sysPath - build first."
}

# Install INF (uncomment when ready)
#& pnputil /add-driver ".\AGXStub.inf" /install
