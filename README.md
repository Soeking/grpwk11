# grpwk11

## ビルド・実行方法
```
$ cd src
$ make

$ ./grpwk file1 file2

(example)
$ ./grpwk ../data/dat0_in ../out/dat0_out
```

CMakeを使ってもいい

## テスト
### LinuxかMac
```
$ cd check
$ sh check.sh
```

これをするとテストケース全パターン実行され、それぞれの一致度を出力する。  
※check.shを実行すればcheck/に移動しなくてもいい。

### Windows
そもそも動かない  
WSLなりで