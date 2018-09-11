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

  printf("CompilerID: %d Major: %d Minor: %d\n", FINGERA_COMPILER,
         FINGERA_COMPILER_MAJOR, FINGERA_COMPILER_MINOR);
  printf("OSID: %d\n", FINGERA_OS);
}