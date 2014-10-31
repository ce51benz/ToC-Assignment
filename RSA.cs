using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Numerics;
namespace TOCASSIGNMENT2CSH
{

    class RSA
    {
        //Since BigInteger cannot declared as const,use this solution instead.
         private static readonly BigInteger TWOPOW30 = new BigInteger(Math.Pow(2, 30));
         private static readonly BigInteger E = new BigInteger(65537);


        //Since prime number is not even number then the first work for this method is
        //Check when preferred number is divisible by 2
        //And then use loop number N from 3 to itself - 1 increase number by 2 every time
        //It loop check that whether preferred number is divisible by N?

         public static bool isPrime(BigInteger num)
         {
             if (num == 1||num == 2) return true;
             else if (num % 2 == 0) return false;
             for (BigInteger i = 3 ; i < num; i+=2)
             {
                 if (num % i == 0)
                     return false;
             }
             return true;
         }

        static void Main(string[] args)
        {
            
            Random generator = new Random();
            BigInteger p, q;
            Console.WriteLine("KMITL TOC1/2557 Assignment 2 Number Theory");
            Console.WriteLine("[Member]");
            Console.WriteLine("1.Maturose Kappako\t55010977");
            Console.WriteLine("2.Suratchanan Kraidech\t55011362");
            Console.WriteLine();
            //Random first number p
            while (true)
            {
                p = new BigInteger(generator.NextDouble() * Math.Pow(2, 32));
                if (p >= TWOPOW30)
                {
                    if (isPrime(p))
                        break;
                }
            }

            Console.WriteLine("p = " + p);

            //random next number q check that p != q too.
            while (true)
            {
                q = new BigInteger(generator.NextDouble() * Math.Pow(2, 32));
                if (q >= TWOPOW30 && q != p)
                {
                    if (isPrime(q))
                        break;
                }
            }
            
            Console.WriteLine("q = " + q);

            //Find n = p x q
            BigInteger n = BigInteger.Multiply(p, q);
            Console.WriteLine("n = " + n);

            //Find phi_n = (p-1) x (q-1)
            BigInteger phi_n = BigInteger.Multiply(p - 1, q - 1);
            Console.WriteLine("phi(n) = " + phi_n);

            //From e x d = 1(mod phi_n)
            //Then d = e^-1 (mod phi_n)
            //But use of BigInteger will result in ZERO value
            //Then use linear loop instead
            BigInteger i = 1;
            BigInteger d;
            while(true)
            {
                if (((phi_n * i) + 1) % E == 0)
                {
                    d = ((phi_n * i) + 1) / E;
                    break;
                }
                i++;
            }

            Console.WriteLine("d = " + d);
            
            //Display public and private key
            Console.WriteLine("Private key(n,d) = (" + n+","+d+")");
            Console.WriteLine("Public key(n,e) = (" + n + "," + E + ")");

            //Member id for each member in group
            BigInteger mem_id1 = new BigInteger(55010977);
            BigInteger mem_id2 = new BigInteger(55011362);

            //Message to send is the multiple result of both members id
            BigInteger m = mem_id1 * mem_id2;
            Console.WriteLine("m = " + m);

            //Encrypt message use public key and result it in c = m^e mod n
            BigInteger c = BigInteger.ModPow(m, E, n);
            Console.WriteLine("c = " + c);

            //c is encrypt message so decrypt it by use private key
            //m' = c^d mod n
            BigInteger mdat = BigInteger.ModPow(c, d, n);
            Console.WriteLine("m' = " + mdat);

            //Check that decrypt message is equal to source message
            if (m == mdat)
            {
                Console.WriteLine("m == m' ? = Succeed");
            }
            else
                Console.WriteLine("m == m' ? = Fail");

            //If public key (for sender that use to send) is not match with desired value
            //The FAIL result will arise
            BigInteger e2 = E + 1;
            BigInteger n2 = n + 1;
            BigInteger c2 = BigInteger.ModPow(m, e2, n2);

            Console.WriteLine();
            Console.WriteLine("Fake public key(n,e) = (" + n2+","+e2+")");
            Console.WriteLine("c fake result = "+c2);
            //The receive use private key to decrypt it will result in FAIL
            mdat = BigInteger.ModPow(c2, d, n);
            Console.WriteLine("m' = "+ mdat);
            if (m == mdat)
            {
                Console.WriteLine("m == m' ? = Succeed");
            }
            else
                Console.WriteLine("m == m' ? = Fail");
            Console.ReadLine();
        }
    }
}
