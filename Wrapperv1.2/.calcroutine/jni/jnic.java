public class jnic
{
        static {
           System.loadLibrary("jnic");
           //System.load("/data/jsoftarchive/lnxtime2/jni/libjnic.so");
	}

       // Native Method
	public native String sayHello(String s);

	public static void main(String[] argv)
	{
		String retval = null;
		jnic nt = new jnic();
		retval = nt.sayHello("Beavis");
		System.out.println("Invocation returned " + retval);
	}
}

