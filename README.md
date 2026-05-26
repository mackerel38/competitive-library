# competitive-library

C++23 用の競技プログラミングライブラリです。

## 必要環境

- C++23 対応コンパイラ。主に `g++` を想定しています。
- `online-judge-verify-helper` (`oj-verify`)

## ディレクトリ構成

- `structure/`: データ構造
- `math/`: 数論、代数、組合せなど
- `geometry/`: 幾何
- `string/`: 文字列アルゴリズム
- `utility/`: 小さな補助関数や共通部品
- `graph/`: グラフアルゴリズム、グラフ用データ構造
- `verify/`: `oj-verify` 用の検証コード
- `docs/`: 各ライブラリの使い方、動作、計算量

## include 方針

リポジトリのルートを include パスに追加して使います。

```cpp
#include "math/modint.hpp"
```

verify コードや手元のコンテストコードでも、この形式に合わせます。

## 検証

すべての verify を実行します。

```sh
oj-verify run
```

必要に応じてドキュメントを生成します。

```sh
oj-verify docs
```

## 方針

- コンテスト中に素早く使えることを優先します。
- よく使う操作は、必要に応じて便利メソッドとして追加します。
- ライブラリを追加したら、できるだけ `verify/` に検証コードも追加します。
- 各ライブラリの使い方、できること、計算量は docs に残します。
