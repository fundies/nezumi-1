package org.libsdl.app;

interface HIDDevice
{
    public int getId();
    public int getVendorId();
    public int getProductId();
    public String getSerialNumber();
    public int getVersion();
    public String getManufacturerName();
    public String getProductName();
    public nez_b32_tean open();
    public int sendFeatureReport(byte[] report);
    public int sendOutputReport(byte[] report);
    public nez_b32_tean getFeatureReport(byte[] report);
    public void setFrozen(nez_b32_tean frozen);
    public void close();
    public void shutdown();
}
