//import java.math;
import java.math.BigInteger;
import java.util.Random;
public class RSA {
	public static final BigInteger TWOPOW30 = new BigInteger("1073741824");
	public static final BigInteger E = new BigInteger("65537");
	public static final BigInteger TWO = new BigInteger("2");
	
	public static boolean isPrime(BigInteger num){
		for(BigInteger i = TWO;
				i.compareTo(num) == -1;i = i.add(BigInteger.ONE)){
		if(num.mod(i) == BigInteger.ZERO)
			return false;
		}
		return true;
	}
	
	public static void main(String[] args) {
		Random generator = new Random(System.currentTimeMillis());
		BigInteger p,q;
		while(true){
			p = new BigInteger(32, generator);
			if(p.compareTo(TWOPOW30) == 1){
				if(isPrime(p))
					break;
			}
		}
		
		while(true){
			q = new BigInteger(32, generator);
			if(q.compareTo(TWOPOW30) == 1){
				if(isPrime(q))
					break;
			}
		}
		
		System.out.print("p = ");
		System.out.println(p);
		System.out.print("q = ");
		System.out.println(q);
		
		BigInteger n = p.multiply(q);
		BigInteger phi_n = p.subtract(BigInteger.ONE).
				           multiply(q.subtract(BigInteger.ONE));
		
		System.out.print("n = ");
		System.out.println(n);
		System.out.print("phi_n = ");
		System.out.println(phi_n);
		
		BigInteger d;
		BigInteger i = BigInteger.ONE;
		while(true){
			if(phi_n.multiply(i).add(BigInteger.ONE).mod(E).
					compareTo(BigInteger.ZERO) == 0){
				d = phi_n.multiply(i).add(BigInteger.ONE).divide(E);
			break;	
			}
			i = i.add(BigInteger.ONE);
		}		
		System.out.print("d = ");
		System.out.println(d);
		System.out.print("Private key = (");
		System.out.print(n);
		System.out.print(",");
		System.out.print(d);
		System.out.println(")");
		System.out.print("Public key = (");
		System.out.print(n);
		System.out.print(",");
		System.out.print(E);
		System.out.println(")");
		//System.out.println((E.multiply(d).mod(phi_n).compareTo(BigInteger.ONE) == 0));
	}
}


