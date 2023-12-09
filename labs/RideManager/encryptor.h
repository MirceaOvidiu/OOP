#include <iostream>
#include <string>
#include <vector>

class Encryptor
{
public:
    // Function to calculate the greatest common divisor
    static int gcd(int a, int b)
    {
        while (b != 0)
        {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    // Function to calculate the modular inverse using extended Euclidean algorithm
    static int modInverse(int a, int m)
    {
        for (int x = 1; x < m; x++)
        {
            if ((a * x) % m == 1)
            {
                return x;
            }
        }
        return -1; // Inverse does not exist
    }

    // Function to perform modular exponentiation (a^b mod m)
    static int modPow(int base, int exponent, int modulus)
    {
        int result = 1;
        base = base % modulus;

        while (exponent > 0)
        {
            if (exponent % 2 == 1)
            {
                result = (result * base) % modulus;
            }
            exponent = exponent >> 1;
            base = (base * base) % modulus;
        }

        return result;
    }

    // Function to generate RSA key pair
    static std::pair<std::pair<int, int>, std::pair<int, int>> generateKeyPair(int p, int q, int e)
    {
        int n = p * q;                   // Calculate n
        int totient = (p - 1) * (q - 1); // Calculate Euler's totient function

        // Calculate private exponent d such that d ≡ e^(-1) (mod totient)
        int d = modInverse(e, totient);

        return std::make_pair(std::make_pair(n, e), std::make_pair(n, d));
    }

    static std::vector<int> encryptMessage(const std::string &message, const std::pair<int, int> &publicKey)
    {
        std::vector<int> ciphertext;

        for (char ch : message)
        {
            int m = static_cast<int>(ch);
            int c = modPow(m, publicKey.second, publicKey.first);
            ciphertext.push_back(c);
        }

        return ciphertext;
    }

    // Function to decrypt a message using RSA private key
    static std::string decryptMessage(const std::vector<int> &ciphertext, const std::pair<int, int> &privateKey)
    {
        std::string plaintext;

        for (int c : ciphertext)
        {
            int m = modPow(c, privateKey.second, privateKey.first);
            plaintext += static_cast<char>(m);
        }

        return plaintext;
    }

    ~Encryptor() = default;
};
