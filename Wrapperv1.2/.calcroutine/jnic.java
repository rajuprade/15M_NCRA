public class jnic
{
        static {
           System.loadLibrary("jcalepochc");
           //System.load("/data/jsoftarchive/lnxtime2/jni/libjnic.so");
	}

       // Native Method
	public native String jcalepochc(String s);

	public static void main(String[] argv)
	{
		String retval = null;
		jnic nt = new jnic();
		retval = nt.jcalepochc(argv[0]);
		System.out.println("Invocation returned " + retval);
	}
}

