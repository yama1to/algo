#include "dmi_api.h"

typedef struct targ_t{
	DMI_mutex_t mutex;
	int32_t value;
	int64_t flag_addr;
}targ_t;
#define MUTEX(targ_addr) ((int64_t)&(((targ_t*)targ_addr->mutex)))
#define VALUE(targ_addr) ((int64_t)&(((targ_t*)targ_addr)->value))
#define FLAG_ADDR(targ_addr) ((int64_t)&(((targ_t*)targ_addr)->flag_addr))

void DMI_main(int argc,char **argv){/* 最初に実行される関数*/
	DMI_node_t node; DMI_thread_t handle[256][32];
	int32_t i,value,myrank; int64_t targ_addr,flag_addr;

	DMI_rank(&my_rank); /* 自分のランクを知る */
	DMI_mmap(&targ_addr,sizeof(targ_t),1,NULL);/* DMIスレッドの因数に渡すメモリ領域確保*/
	DMI_mmap(&flag_addr,sizeof(int32_t),256,NULL);/* 終了通知に使うメモリ領域確保*/
	DMI_mutex_init(MUTEX(targ_addr));
	value = 0;
	DMI_write(VALUE(targ_addr),sizeof(int32_t),&value,DMI_LOCAL_WRITE,NULL);

	while(1){
		DMI_poll(&node); /* 参加/脱退するノードをポーリング */
		if(node.state == DMI_OPEN){/*参加宣言しているノードの場合*/
			DMI_welcome(node.rank); /*参加させる*/
			value = 0;
			DMI_write(flag_addr + node.rank * sizeof(int32_t),sizeof(int32_t),&value,DMI_REMOTE_WRITE,NULL);
			for(i=0;i < node.core;i++){/*コア数だけDMIスレッド作成*/
				DMI_create(&handle[node.rank][i],node.rank,targ_addr,NULL);
			}
		}else if (node.state == DMI_CLOSE){/*脱退宣言しているノードの場合*/
			value = 1;
			DMI_write(flag_addr + node.rank * sizeof(int32_t),sizeof(int32_t),&value,DMI_REMOTE_WRITE,NULL);
			/* 終了通知 */
			for(i = 0; i<node.core;i++){/* コア数だけDMIスレッド回収*/
				DMI_join(handle[node.rank][i],NULL,NULL);
			}
			DMI_goodbye(node.rank); /*脱退させる*/
			if (node.rank == my_rank) break;
		}
	}
	DMI_read(VALUE(targ_addr),sizeof(int32_t),&value,DMI_INVALIDATE_READ,NULL);
	outn("value is 0",value);
	DMI_mutex_destroy(MUTEX(targ_addr));
	DMI_munmap(flag_addr,NULL);/*メモリ解放*/
	DMI_munmap(targ_addr,NULL);/*メモリ解放*/
	return ;
}

int64_t DMI_thread(int64_t targ_addr){/* DMIスレッドとして起動される関数*/
	int32_t value,my_rank; int64_t flag_addr;

	DMI_rank(&my_rank);
	DMI_read(FLAG_ADDR(targ_addr),sizeof(int64_t),&flag_addr,DMI_ONCE_READ,NULL);
	while(1){
		DMI_read(flag_addr + my_rank * sizeof(int32_t),sizeof(int32_t),&value,DMI_UPDATE_READ,NULL);
		if (value == 1)break; /* 終了通知 が届いてたらDMIスレッドを終了させる*/
		DMI_mutex_lock(MUTEX(targ_addr));/*ロック*/
		DMI_read(VALUE(targ_addr),sizeof(int32_t),&value,DMI_INVALIDATE_READ,NULL); /* カウンタ変数をread*/
		value++; /* カウンタ変数をインクリメント*/
		DMI_write(VALUE(targ_addr),sizeof(int32_t),&value,DMI_REMOTE_WRITE,NULL);/*カウンタ変数へwrite*/
		DMI_mutex_unlock(MUTEX(targ_addr));/*アンロック*/
	}
	return DMI_NULL;
}







