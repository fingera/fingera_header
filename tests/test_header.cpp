#include <fingera/header.h>

#include <stdio.h>

#include <gtest/gtest.h>

TEST(fingera_header, all) {
  uint8_t buffer[] = {
      0, 1, 2, 3, 4, 5, 6, 7,
  };
  uint8_t write_buf[8];

  cleanse(write_buf, sizeof(write_buf));

  size_t unused_var = _countof_(write_buf);
  _unused_(unused_var);

  EXPECT_EQ(readle16(buffer), 0x0100);
  EXPECT_EQ(readbe16(buffer), 0x0001);
  EXPECT_EQ(readle32(buffer), 0x03020100ul);
  EXPECT_EQ(readbe32(buffer), 0x00010203ul);
  EXPECT_EQ(readle64(buffer), 0x0706050403020100ull);
  EXPECT_EQ(readbe64(buffer), 0x0001020304050607ull);

  EXPECT_EQ(readle<uint8_t>(buffer), 0x00);
  EXPECT_EQ(readbe<uint8_t>(buffer), 0x00);
  EXPECT_EQ(readle<uint16_t>(buffer), 0x0100);
  EXPECT_EQ(readbe<uint16_t>(buffer), 0x0001);
  EXPECT_EQ(readle<uint32_t>(buffer), 0x03020100ul);
  EXPECT_EQ(readbe<uint32_t>(buffer), 0x00010203ul);
  EXPECT_EQ(readle<uint64_t>(buffer), 0x0706050403020100ull);
  EXPECT_EQ(readbe<uint64_t>(buffer), 0x0001020304050607ull);

  writele16(write_buf, 0x0100);
  EXPECT_FALSE(memcmp(write_buf, buffer, 2));
  writebe16(write_buf, 0x0001);
  EXPECT_FALSE(memcmp(write_buf, buffer, 2));
  writele32(write_buf, 0x03020100ul);
  EXPECT_FALSE(memcmp(write_buf, buffer, 4));
  writebe32(write_buf, 0x00010203ul);
  EXPECT_FALSE(memcmp(write_buf, buffer, 4));
  writele64(write_buf, 0x0706050403020100ull);
  EXPECT_FALSE(memcmp(write_buf, buffer, 8));
  writebe64(write_buf, 0x0001020304050607ull);
  EXPECT_FALSE(memcmp(write_buf, buffer, 8));

  writele(write_buf, (uint8_t)0x00);
  EXPECT_FALSE(memcmp(write_buf, buffer, 1));
  writebe(write_buf, (uint8_t)0x00);
  EXPECT_FALSE(memcmp(write_buf, buffer, 1));
  writele(write_buf, (uint16_t)0x0100);
  EXPECT_FALSE(memcmp(write_buf, buffer, 2));
  writebe(write_buf, (uint16_t)0x0001);
  EXPECT_FALSE(memcmp(write_buf, buffer, 2));
  writele(write_buf, (uint32_t)0x03020100ul);
  EXPECT_FALSE(memcmp(write_buf, buffer, 4));
  writebe(write_buf, (uint32_t)0x00010203ul);
  EXPECT_FALSE(memcmp(write_buf, buffer, 4));
  writele(write_buf, (uint64_t)0x0706050403020100ull);
  EXPECT_FALSE(memcmp(write_buf, buffer, 8));
  writebe(write_buf, (uint64_t)0x0001020304050607ull);
  EXPECT_FALSE(memcmp(write_buf, buffer, 8));

  // https://en.wikipedia.org/wiki/Single-precision_floating-point_format
  const uint8_t float_one[] = {
      0x3f,
      0x80,
      0x00,
      0x00,
  };
  const uint8_t float_one_le[] = {
      0x00,
      0x00,
      0x80,
      0x3f,
  };
  EXPECT_EQ(readbe<float>(float_one), 1.0f);
  EXPECT_EQ(readle<float>(float_one_le), 1.0f);
  writebe(write_buf, (float)1.0f);
  EXPECT_FALSE(memcmp(write_buf, float_one, 4));
  writele(write_buf, (float)1.0f);
  EXPECT_FALSE(memcmp(write_buf, float_one_le, 4));
  const uint8_t double_one[] = {
      0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  };
  const uint8_t double_one_le[] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f,
  };
  EXPECT_EQ(readbe<double>(double_one), 1.0);
  EXPECT_EQ(readle<double>(double_one_le), 1.0);
  writebe(write_buf, (double)1.0);
  EXPECT_FALSE(memcmp(write_buf, double_one, 8));
  writele(write_buf, (double)1.0);
  EXPECT_FALSE(memcmp(write_buf, double_one_le, 8));

  printf("CompilerID: %d Major: %d Minor: %d\n", FINGERA_COMPILER,
         FINGERA_COMPILER_MAJOR, FINGERA_COMPILER_MINOR);
  printf("OSID: %d\n", FINGERA_OS);
}