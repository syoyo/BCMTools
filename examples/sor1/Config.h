/*
 * BCMTools
 *
 * Copyright (C) 2011-2014 Institute of Industrial Science, The University of Tokyo.
 * All rights reserved.
 *
 * Copyright (c) 2012-2014 Advanced Institute for Computational Science, RIKEN.
 * All rights reserved.
 *
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <string>
#include <vector>
#include "ConfigBase.h"
#include "Vec3.h"

using namespace Vec3class;

class Config : public ConfigBase {

public:

  int minLevel;  ///< 最小分割レベル
  int maxLevel;  ///< 最大分割レベル

  std::string treeType;  ///< ツリータイプ

  std::string ordering;  ///< オーダリング方法

  char type;             ///< 固定境界の向き
  double b0, b1;         ///< 境界値

  int nLoopInner;
  int nLoopOuter;

  double omega;

  bool separate;         ///< 方向毎仮想セル同期フラグ

  int size;   ///< ブロック内セル分割数
  int vc;     ///< 仮想セル幅

  std::string output;  ///< 結果出力ファイル(未使用)
  bool verbose;          ///< 冗長メッセージフラグ

private:

  void parse() {
    minLevel = read<int>("minLevel", 0);
    maxLevel = read<int>("maxLevel");
    treeType = read<string>("treeType");
    ordering = read<string>("ordering");

    type = read<char>("type");

    b0 = read<double>("b0", 0.0);
    b1 = read<double>("b1", 1.0);

    nLoopInner = read<int>("nLoopInner");
    nLoopOuter = read<int>("nLoopOuter");

    omega = read<double>("omega", 1.0);

    separate = read<bool>("separateVCUpdate", false);

    size = read<int>("size");
    vc = read<int>("vc");

    output = read<string>("output");

    verbose = read<bool>("verbose", false);

  }

  bool validate() {
    bool ret = true;
    if (!(treeType == "flat" || treeType == "simple")) {
      std::cout << "error: 'treeType' must be 'flat' or 'simple'." << std::endl;
      ret = false;
    }

    if (!(ordering == "Z" || ordering == "Hilbert" || ordering == "random")) {
      std::cout << "error: 'ordering' must be 'Z', 'Hilbert' or 'random'."
                << std::endl;
      ret = false;
    }
    if (size < 1) {
      std::cout << "error: 'size' must be > 1" << std::endl;
      ret = false;
    }
    if (!(vc > 0 && vc <= size/2)) {
      std::cout << "error: 'vc' must be 0 < vc && vc <= size/2." << std::endl;
      ret = false;
    }
    if (!(minLevel >= 0)) {
      std::cout << "error: 'minLevel' must be >= 0." << std::endl;
      ret = false;
    }
    if (!(minLevel <= maxLevel)) {
      std::cout << "error: 'minLevel' and 'maxLevel'  must be minLevel <= maxLevel." << std::endl;
      ret = false;
    }
    switch (type) {
      case 'X':
        type = 'x';
        break;
      case 'Y':
        type = 'y';
        break;
      case 'Z':
        type = 'z';
        break;
      case 'x':
      case 'y':
      case 'z':
        break;
      default:
        std::cout << "error: 'type' must be 'x', 'y' or 'z'." << std::endl;
        ret = false;
        break;
    }

    return ret;
  }

public:

  void print() const {
    std::cout.setf(std::ios::showpoint);
    std::cout << "  min level:          " << minLevel << std::endl;
    std::cout << "  max level:          " << maxLevel << std::endl;
    std::cout << "  tree type:          " << treeType << std::endl;
    std::cout << "  type:               " << type << std::endl;
    std::cout << "  ordering:           " << ordering << std::endl;
    std::cout << "  block size:         " << size << std::endl;
    std::cout << "  vc width:           " << vc << std::endl;
    std::cout << "  boundary values:    " << b0 << ", " << b1 << std::endl;
    std::cout << "  SOR oemga:          " << omega << std::endl;
    std::cout << "  inner loop length:  " << nLoopInner << std::endl;
    std::cout << "  outer loop length:  " << nLoopOuter << std::endl;
    std::cout << "  output file:        " << output << std::endl;
    std::cout << "  verbose message:    " << (verbose ? "on" : "off") << std::endl;
  }

};



#endif // CONFIG_H
