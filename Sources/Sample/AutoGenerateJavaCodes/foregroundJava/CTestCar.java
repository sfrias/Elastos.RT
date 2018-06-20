
package org.elastos.Elastos.AutoGenerateJavaCodes;

//this java class will implement the elastos interface.
public class CTestCar implements ITestCar {
    static {
        System.loadLibrary("Elastos.Runtime");
        System.loadLibrary("Elastos.CoreLibrary");
        System.loadLibrary("Elastos.AutoGenerateJavaCodes");
        //TODO : Your jni so, please fill it.
        System.loadLibrary("Your_Jni");
    }

    private long mCarObj = 0;

    private native long native_CTestCar(double[] dArray, String[] sArray);
    private native long native_CTestCar(IServiceManager sm, ICarrier carrier);
    private native void native_CTestCar_Destroy(long carobj);

    public CTestCar(double[] dArray, String[] sArray) {
        mCarObj = native_CTestCar(dArray, sArray);
        //TODO: Add your code here
    }

    public CTestCar(IServiceManager sm, ICarrier carrier) {
        mCarObj = native_CTestCar(sm, carrier);
        //TODO: Add your code here
    }

    public long getCarObject() {
        return mCarObj;
    }

    // invoke destroy to release car object
    public void destroy() {
        native_CTestCar_Destroy(mCarObj);
    }


    public void SetInt(
        /* [in] */ int value) {
        //TODO: Add your code here
    }

    public int GetInt() {
        //TODO: Add your code here
        return 0;
    }

    public void SetString(
        /* [in] */ String value) {
        //TODO: Add your code here
    }

    public String GetString() {
        //TODO: Add your code here
        return "NULL";
    }

    public void Normal() {
        //TODO: Add your code here
    }

    public void Test1(
        /* [in] */ int value1,
        /* [in] */ boolean value2,
        /* [in] */ float value3,
        /* [in] */ double value4,
        /* [in] */ long value5,
        /* [in] */ byte value6,
        /* [in] */ char value7,
        /* [in] */ String value8) {
        //TODO: Add your code here
    }

    public int Test2(
        /* [in] */ int value1,
        /* [in] */ boolean value2,
        /* [in] */ float value3,
        /* [in] */ double value4,
        /* [in] */ long value5,
        /* [in] */ byte value6,
        /* [in] */ char value7,
        /* [in] */ String value8,
        /* [in] */ String value9,
        /* [in] */ String value10) {
        //TODO: Add your code here
        return 0;
    }

    public void Test7(
        /* [in] */ IHelloCar animal) {
        //TODO: Add your code here
    }

    public IHelloCar Test8() {
        //TODO: Add your code here
        return null;
    }

    public void Test9(
        /* [in] */ ICarrier[] carriers) {
        //TODO: Add your code here
    }

    public ICarrier[] Test10() {
        //TODO: Add your code here
        return null;
    }


}
