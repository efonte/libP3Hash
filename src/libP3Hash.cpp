#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <climits> // for CHAR_BIT

#include "libP3Hash.h"

namespace patapon {

    void P3Hasher::aaa() {
        t3 = t3 ^ hashTable[(0x401 + (((t4 >> 0x18) & 0xFF) << 0x2)) / 4];
        t2 = hashTable[(0x801 + (((t4 >> 0x10) & 0xFF) << 0x2)) / 4];
        t1 = hashTable[(0xC01 + (((t4 >> 0x8) & 0xFF) << 0x2)) / 4];
        t4 = magicTable[++offset];
        t1 = t1 ^ (t2 ^ t3);
        t5 = hashTable[((0x8A6A2BC + (((t6 >> 0x18) & 0xFF) << 0x2)) - 0x8A6A2BB) / 4] ^ hashTable[((0x8A6A6BC + (((t6 >> 0x10) & 0xFF) << 0x2)) - 0x8A6A2BB) / 4];
        t2 = 0x8A6AEBC + ((t6 & 0xFF) << 0x2);
        t3 = magicTable[++offset];
        t5 = hashTable[(t2 - 0x8A6A2BB) / 4] ^ (hashTable[((0x8A6AABC + (((t6 >> 0x8) & 0xFF) << 0x2)) - 0x8A6A2BB) / 4] ^ t5);
    }

    void P3Hasher::ccc() {
        t2 = _a1_0x0;
        t4 = t5 ^ t4;
        t3 = (t1 ^ t3) ^ t4;
        _a1_0x0 = t2 ^ t3;
        t2 = ((t4 >> 0x8) + (t4 << 0x18)) ^ t3;
        t1 = _a1_0x4;
    }

    void P3Hasher::ddd() {
        t2 = _a1_0x8;
        t3 = (t1 ^ t3) ^ (t5 ^ t4);
        t1 = t2 ^ t3;
        _a1_0x8 = t1;
        t2 = (((t5 ^ t4) >> 0x8) + ((t5 ^ t4) << 0x18)) ^ t3;
        t1 = _a1_0xC;
        t4 = t1 ^ t2;
        t3 = hashTable[(0x1 + ((t4 & 0xFF) << 0x2)) / 4];
        _a1_0xC = t4;
        t6 = _a1_0x8;
    }

    std::pair<uint32_t, uint32_t> P3Hasher::decrypt_two_values(uint32_t var1, uint32_t var2) {
        uint32_t t1 = hashTable[0x300 + ((var1 / 0x100) & 0xFF)] ^ (hashTable[0x200 + ((var1 / 0x10000) & 0xFF)] ^ (hashTable[var1 & 0xFF] ^ hashTable[0x100 + ((var1 / 0x1000000) & 0xFF)]));
        uint32_t t4 = hashTable[0x300 + (var2 & 0xFF)] ^ (hashTable[0x200 + ((var2 / 0x100) & 0xFF)] ^ (hashTable[(var2 / 0x1000000) & 0xFF] ^ hashTable[0x100 + ((var2 / 0x10000) & 0xFF)]));
        return std::make_pair(t1, t4); // replace by return {t1, t4} ?
    }


    std::vector<uint32_t> P3Hasher::encryptBlock(std::vector<uint32_t> block) {
        _a1_0x0 = swap_endian<uint32_t>(block[0]);
        _a1_0x4 = swap_endian<uint32_t>(block[1]);
        _a1_0x8 = swap_endian<uint32_t>(block[2]);
        _a1_0xC = swap_endian<uint32_t>(block[3]);

        offset = 3;

        a2 = magicTable[0];
        _a1_0x0 = _a1_0x0 ^ a2;
        t2 = magicTable[1];
        t1 = _a1_0x4;
        t4 = t1 ^ t2;
        t3 = hashTable[(0x1 + ((t4 & 0xFF) << 0x2)) / 4];
        _a1_0x4 = t4;
        t6 = _a1_0x0;
        aaa();

        for (int i = 0; i < 3; i++) {
            ddd();
            aaa();
            ccc();
            t4 = t1 ^ t2;
            t3 = hashTable[(0x1 + ((t4 & 0xFF) << 0x2)) / 4];
            _a1_0x4 = t4;
            t6 = _a1_0x0;
            aaa();
            ddd();
            aaa();
            ccc();
            t4 = t1 ^ t2;
            t3 = hashTable[(0x1 + ((t4 & 0xFF) << 0x2)) / 4];
            _a1_0x4 = t4;
            t6 = _a1_0x0;
            aaa();
            ddd();
            aaa();
            ccc();
            t3 = t1 ^ t2;
            t2 = magicTable[++offset];
            t1 = t2 & _a1_0x0;
            t2 = t1 << 0x1;
            t1 = t2 + (t1 >> 0x1F);
            t3 = t3 ^ t1;
            _a1_0x4 = t3;
            t2 = magicTable[++offset];
            t1 = _a1_0x0;
            t2 = t2 | t3;
            t1 = t1 ^ t2;
            _a1_0x0 = t1;
            t3 = magicTable[offset + 2];
            t2 = _a1_0xC;
            t1 = _a1_0x8;
            t2 = t3 | t2;
            t3 = t1 ^ t2;
            _a1_0x8 = t3;
            t2 = magicTable[offset + 1];
            offset = offset + 2;
            t1 = _a1_0xC;
            t2 = t2 & t3;
            t3 = t2 << 0x1;
            t2 = t2 >> 0x1F;
            t2 = t3 + t2;
            t1 = t1 ^ t2;
            _a1_0xC = t1;
            t5 = _a1_0x4;
            t6 = _a1_0x0;
            t4 = magicTable[++offset];
            t3 = hashTable[((0x8A6A2BC + ((t5 & 0xFF) << 0x2)) - 0x8A6A2BB) / 4];
            t1 = (t5 >> 0x18) & 0xFF;
            t1 = t1 << 0x2;
            t2 = hashTable[(0x401 + t1) / 4];
            t1 = (t5 >> 0x10) & 0xFF;
            t1 = t1 << 0x2;
            t3 = t3 ^ t2;
            t2 = hashTable[(0x801 + t1) / 4];
            t1 = (t5 >> 0x8) & 0xFF;
            t1 = t1 << 0x2;
            t5 = t2 ^ t3;

            t3 = hashTable[(0xC01 + t1) / 4];
            t2 = ((t6 >> 0x18) & 0xFF) << 0x2;
            t1 = t3 ^ t5;
            t5 = hashTable[(0x1 + t2) / 4];
            t3 = hashTable[((0x8A6A6BC + (((t6 >> 0x10) & 0xFF) << 0x2)) - 0x8A6A2BB) / 4];
            t2 = ((t6 >> 0x8) & 0xFF) << 0x2;
            t5 = t5 ^ t3;
            t3 = hashTable[(0x801 + t2) / 4];
            t2 = (t6 & 0xFF) << 0x2;
            t6 = t3 ^ t5;
            t5 = hashTable[(0xC01 + t2) / 4];
            t3 = magicTable[++offset];
            t5 = t5 ^ t6;
        }

        ddd();
        aaa();
        ccc();
        t4 = t1 ^ t2;
        t3 = hashTable[(0x1 + ((t4 & 0xFF) << 0x2)) / 4];
        _a1_0x4 = t4;
        t6 = _a1_0x0;
        aaa();
        ddd();
        aaa();
        ccc();
        t4 = t1 ^ t2;
        t3 = hashTable[(0x1 + ((t4 & 0xFF) << 0x2)) / 4];
        _a1_0x4 = t4;
        t6 = _a1_0x0;
        aaa();
        t2 = _a1_0x8;
        t4 = t5 ^ t4;
        t1 = t1 ^ t3;
        t3 = t1 ^ t4;
        t1 = t2 ^ t3;
        _a1_0x8 = t1;
        t2 = t4 >> 0x8;
        t1 = t2 + (t4 << 0x18);
        t2 = t1 ^ t3;
        t1 = _a1_0xC;
        t4 = t1 ^ t2;
        t3 = hashTable[(0x1 + ((t4 & 0xFF) << 0x2)) / 4];
        _a1_0xC = t4;
        t3 = t3 ^ hashTable[(0x401 + (((t4 >> 0x18) & 0xFF) << 0x2)) / 4];  // aaa();
        t2 = hashTable[(0x801 + (((t4 >> 0x10) & 0xFF) << 0x2)) / 4];
        t1 = 0x8A6AEBC + (((t4 >> 0x8) & 0xFF) << 0x2);
        t3 = t2 ^ t3;
        t1 = hashTable[(t1 - 0x8A6A2BB) / 4];
        t4 = _a1_0x8;
        t2 = magicTable[++offset];
        t1 = t1 ^ t3;
        t3 = ((t4 >> 0x18) & 0xFF) << 0x2;
        t3 = hashTable[((0x8A6A2BC + t3) - 0x8A6A2BB) / 4];
        t0 = ((t4 >> 0x10) & 0xFF) << 0x2;
        a3 = 0x8A6A6BC + t0;
        t0 = hashTable[(a3 - 0x8A6A2BB) / 4];
        a3 = ((t4 >> 0x8) & 0xFF) << 0x2;
        a2 = 0x8A6AABC + a3;
        a3 = hashTable[(a2 - 0x8A6A2BB) / 4];
        t0 = t3 ^ t0;
        a2 = (t4 & 0xFF) << 0x2;
        v1 = 0x8A6AEBC + a2;
        t0 = a3 ^ t0;
        a3 = hashTable[(v1 - 0x8A6A2BB) / 4];
        a2 = magicTable[++offset];
        a3 = a3 ^ t0;
        v1 = _a1_0x0;
        t0 = a3 ^ t2;
        a2 = t1 ^ a2;
        a3 = a2 ^ t0;
        v1 = v1 ^ a3;
        _a1_0x0 = v1;
        a2 = t0 >> 0x8;
        v1 = a2 + (t0 << 0x18);
        a2 = v1 ^ a3;
        v1 = _a1_0x4 ^ a2;
        _a1_0x4 = v1;
        a2 = magicTable[++offset];
        v1 = _a1_0x8 ^ a2;
        _a1_0x8 = v1;
        a0 = magicTable[++offset];
        v1 = _a1_0xC ^ a0;
        _a1_0xC = v1;
        a2 = _a1_0x0;
        a0 = _a1_0x4;
        v1 = _a1_0x8;
        _a1_0x0 = v1;
        v1 = _a1_0xC;
        _a1_0x4 = v1;
        _a1_0x8 = a2;
        _a1_0xC = a0;

        uint32_t a = swap_endian<uint32_t>(_a1_0x0);
        uint32_t b = swap_endian<uint32_t>(_a1_0x4);
        uint32_t c = swap_endian<uint32_t>(_a1_0x8);
        uint32_t d = swap_endian<uint32_t>(_a1_0xC);

        std::vector<uint32_t> f = {a, b, c, d};
        return f;
    }

    std::vector<uint32_t> P3Hasher::decryptBlock(std::vector<uint32_t> block) {
        uint32_t b0 = swap_endian<uint32_t>(block[0]);
        uint32_t b4 = swap_endian<uint32_t>(block[1]);
        uint32_t b8 = swap_endian<uint32_t>(block[2]);
        uint32_t bc = swap_endian<uint32_t>(block[3]);

        uint32_t t4;
        uint32_t t1;
        std::pair<uint32_t, uint32_t> result;
        uint32_t offset = 0x42;

        b4 = b4 ^ magicTable[--offset];
        b0 = b0 ^ magicTable[--offset];
        result = decrypt_two_values(b4, b0);
        t1 = result.first ^ magicTable[--offset];
        t4 = result.second ^ magicTable[--offset];

        for (int i = 0; i <= 3; i++) {
            bc = bc ^ (((t4 / 0x100) + (t4 * 0x1000000)) ^ (t1 ^ t4));
            b8 = b8 ^ (t1 ^ t4);
            result = decrypt_two_values(bc, b8);
            t1 = result.first ^ magicTable[--offset];
            t4 = result.second ^ magicTable[--offset];

            b4 = b4 ^ (((t4 / 0x100) + (t4 * 0x1000000)) ^ (t1 ^ t4));
            b0 = b0 ^ (t1 ^ t4);
            result = decrypt_two_values(b4, b0);
            t1 = result.first ^ magicTable[--offset];
            t4 = result.second ^ magicTable[--offset];

            bc = bc ^ (((t4 / 0x100) + (t4 * 0x1000000)) ^ (t1 ^ t4));
            b8 = b8 ^ (t1 ^ t4);
            result = decrypt_two_values(bc, b8);
            t1 = result.first ^ magicTable[--offset];
            t4 = result.second ^ magicTable[--offset];

            b4 = b4 ^ (((t4 / 0x100) + (t4 * 0x1000000)) ^ (t1 ^ t4));
            b0 = b0 ^ (t1 ^ t4);
            result = decrypt_two_values(b4, b0);
            t1 = result.first ^ magicTable[--offset];
            t4 = result.second ^ magicTable[--offset];

            bc = bc ^ (((t4 / 0x100) + (t4 * 0x1000000)) ^ (t1 ^ t4));
            b8 = b8 ^ (t1 ^ t4);
            result = decrypt_two_values(bc, b8);
            t1 = result.first ^ magicTable[--offset];
            t4 = result.second ^ magicTable[--offset];

            if (i != 3) {
                b4 = (b4 ^ (((t4 / 0x100) + (t4 * 0x1000000)) ^ (t1 ^ t4))) ^ (((magicTable[offset - 2] & (b0 ^ (t1 ^ t4))) * 0x2) + ((magicTable[offset - 2] & (b0 ^ (t1 ^ t4))) / 0x80000000));
                b0 = (b0 ^ (t1 ^ t4)) ^ (magicTable[offset - 1] | b4);
                offset = offset - 2;

                b8 = b8 ^ (magicTable[--offset] | bc);
                offset = offset - 1;
                bc = bc ^ (((magicTable[offset] & b8) * 0x2) + ((magicTable[offset] & b8) / 0x80000000));
                result = decrypt_two_values(b4, b0);
                t1 = result.first ^ magicTable[--offset];
                t4 = result.second ^ magicTable[--offset];
            }
        }

        uint32_t a = b8 ^ magicTable[0x0];
        uint32_t b = bc ^ magicTable[0x1];
        uint32_t c = b0 ^ (t1 ^ t4);
        uint32_t d = b4 ^ (((t4 / 0x100) + (t4 * 0x1000000)) ^ (t1 ^ t4));

        a = swap_endian<uint32_t>(a);
        b = swap_endian<uint32_t>(b);
        c = swap_endian<uint32_t>(c);
        d = swap_endian<uint32_t>(d);

        return {a, b, c, d};
    }

    // Not implemented
    std::vector<char> P3Hasher::encryptRawData(std::vector<char> data) {
        return std::vector<char>();
    }
    std::vector<char> P3Hasher::decryptRawData(std::vector<char> data) {
        return std::vector<char>();
    }

    void P3Hasher::encryptFile(std::string in, std::string out) {
        std::ifstream infile(in, std::ios::binary | std::ios::ate);
        if (!infile) {
            std::cout << "Cannot open " << in << ", process aborted!\n";
            return;
        }

        std::ofstream outfile(out, std::ios::binary | std::ios::trunc);
        if (!outfile) {
            std::cout << "Cannot open " << out << ", process aborted!\n";
        }

        int insize = infile.tellg() / 16;
        infile.seekg(0);

        std::vector<std::vector<uint32_t>> v_out;

        std::cout << "Encrypting file..." << std::endl;
        for (int i = 0; i < insize; i++) {
            uint32_t a, b, c, d;

            infile.read(reinterpret_cast<char *>(&a), sizeof(uint32_t));
            infile.read(reinterpret_cast<char *>(&b), sizeof(uint32_t));
            infile.read(reinterpret_cast<char *>(&c), sizeof(uint32_t));
            infile.read(reinterpret_cast<char *>(&d), sizeof(uint32_t));

            std::vector<uint32_t> bl = {a, b, c, d};
            bl = encryptBlock(bl);
            v_out.push_back(bl);

            if (i % 100000 == 0)
                std::cout << i << " of " << insize << std::endl;
        }

        // now v_out.size() == insize

        if (insize % 100000 != 0)
            std::cout << insize << " of " << insize << std::endl;
        infile.close();

        std::cout << "Saving file..." << std::endl;
        for (int i = 0; i < v_out.size(); i++) {
            outfile.write(reinterpret_cast<char *>(&v_out[i][0]), sizeof(uint32_t));
            outfile.write(reinterpret_cast<char *>(&v_out[i][1]), sizeof(uint32_t));
            outfile.write(reinterpret_cast<char *>(&v_out[i][2]), sizeof(uint32_t));
            outfile.write(reinterpret_cast<char *>(&v_out[i][3]), sizeof(uint32_t));

            if (i % 100000 == 0)
                std::cout << i << " of " << std::to_string(v_out.size()) << std::endl;  // why std::to_string and why v_out.size()?
        }

        if (insize % 100000 != 0)
            std::cout << insize << " of " << insize << std::endl;

        outfile.close();
    }

    void P3Hasher::decryptFile(std::string in, std::string out) {
        std::ifstream infile(in, std::ios::binary | std::ios::ate);
        if (!infile) {
            std::cout << "Cannot open " << in << ", process aborted!\n";
            return;
        }

        std::ofstream outfile(out, std::ios::binary | std::ios::trunc);
        if (!outfile) {
            std::cout << "Cannot open " << out << ", process aborted!\n";
        }

        int insize = infile.tellg() / 16;
        infile.seekg(0);

        std::vector<std::vector<uint32_t>> v_out;

        std::cout << "Decrypting file..." << std::endl;
        for (int i = 0; i < insize; i++) {
            uint32_t a, b, c, d;

            infile.read(reinterpret_cast<char *>(&a), sizeof(uint32_t));
            infile.read(reinterpret_cast<char *>(&b), sizeof(uint32_t));
            infile.read(reinterpret_cast<char *>(&c), sizeof(uint32_t));
            infile.read(reinterpret_cast<char *>(&d), sizeof(uint32_t));

            std::vector<uint32_t> bl = {a, b, c, d};

            if (a + b + c + d != 0x0)
                bl = decryptBlock(bl);

            v_out.push_back(bl);

            if (i % 100000 == 0)
                std::cout << i << " of " << insize << std::endl;
        }

        // now v_out.size() == insize

        if (insize % 100000 != 0)
            std::cout << insize << " of " << insize << std::endl;
        infile.close();

        std::cout << "Saving file..." << std::endl;
        for (int i = 0; i < v_out.size(); i++) {
            outfile.write(reinterpret_cast<char *>(&v_out[i][0]), sizeof(uint32_t));
            outfile.write(reinterpret_cast<char *>(&v_out[i][1]), sizeof(uint32_t));
            outfile.write(reinterpret_cast<char *>(&v_out[i][2]), sizeof(uint32_t));
            outfile.write(reinterpret_cast<char *>(&v_out[i][3]), sizeof(uint32_t));

            if (i % 100000 == 0)
                std::cout << i << " of " << insize << std::endl;
        }

        if (v_out.size() % 100000 != 0)
            std::cout << insize << " of " << insize << std::endl;

        outfile.close();
    }

}