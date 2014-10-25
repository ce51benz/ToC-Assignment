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
         private static readonly BigInteger TWOPOW30 = new BigInteger(Math.Pow(2, 30));
         private static readonly BigInteger E = new BigInteger(65537);

         public static bool isPrime(BigInteger num)
         {
             for (BigInteger i = BigInteger.One + BigInteger.One; i < num; i++)
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
            while (true)
            {
                p = new BigInteger(generator.NextDouble() * Math.Pow(2, 32));
                if (p >= TWOPOW30)
                {
                    if (isPrime(p))
                        break;
                }
            }

            while (true)
            {
                q = new BigInteger(generator.NextDouble() * Math.Pow(2, 32));
                if (q >= TWOPOW30 && q != p)
                {
                    if (isPrime(q))
                        break;
                }
            }

            Console.WriteLine("p = " + p);
            Console.WriteLine("q = " + q);

            BigInteger n = BigInteger.Multiply(p, q);

            Console.WriteLine("n = " + n);

            BigInteger phi_n = BigInteger.Multiply(p - 1, q - 1);

            Console.WriteLine("phi(n) = " + phi_n);
            BigInteger d;
            for (BigInteger i = BigInteger.One; ; i++)
            {
                if (((phi_n * i) + 1) % E == 0)
                {
                    d = ((phi_n * i) + 1) / E;
                    break;
                }
            }

            Console.WriteLine("d = " + d);
            Console.WriteLine("Private key(n,d) = (" + n+","+d+")");
            Console.WriteLine("Public key(n,e) = (" + n + "," + E + ")");
            BigInteger memberid1 = new BigInteger(55010977);
            BigInteger memberid2 = new BigInteger(55011362);
            BigInteger m = memberid1 * memberid2;
            Console.WriteLine("m = " + m);
            BigInteger c = BigInteger.ModPow(m, E, n);
            Console.WriteLine("c = " + c);
            BigInteger mdat = BigInteger.ModPow(c, d, n);
            Console.WriteLine("m' = " + mdat);
            if (m == mdat)
            {
                Console.WriteLine("m == m' ? = Succeed");
            }
            else
                Console.WriteLine("m == m' ? = Fail");
        }
    }
}
