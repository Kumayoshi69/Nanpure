# CMakeList.txt : NanpureCPP の CMake プロジェクト。ソースを含めて、次を定義します:
# プロジェクト専用ロジックはこちらです。
#
cmake_minimum_required (VERSION 3.8)

# ソースをこのプロジェクトの実行可能ファイルに追加します。
add_executable (NanpureCPP "NanpureCPP.cpp" "NanpureCPP.h" "NanpureLib.c" "NanpureLib.h")

# TODO: テストを追加し、必要な場合は、ターゲットをインストールします。
