#ifndef ALLHEADER_H
#define ALLHEADER_H

#define debug true

#ifdef debug
#if debug
//dfs生成
#define dfs_flush_debug true
//dfs解密
#define dfs_decrypt_debug true

#else
//dfs生成
#define dfs_flush_debug false
//dfs解密
#define dfs_decrypt_debug false

#endif
#endif

#endif //  ALLHEADER_H
