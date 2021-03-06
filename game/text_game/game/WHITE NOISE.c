#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int win_1;				//勝利条件
int win_2;				//勝利条件2
int lose;				//敗北条件
int move;				//移動回数の制限
int present;			//現在の位置
char c;					//enter用
char ans1[10];			//応え用
int last_inventory;
int move_select1;
int dir_select;
int i = 13;//
int p_i = 13;
int hint1 = 0;
int k = 0;
int pass;
int game = 1;
char name[100];


struct room {	//部屋はデータ構造体

	char room_name[50];		//現在の位置：現在位置は文字で表す。各部屋ごとに名前があります。
	char question[5000];		//謎の問題：謎が現れる場合、謎の問題を画面に表示する。
	char hint[50];			//ヒント：ヒントを選択した場合は問題に関連するヒントを表示する。
	char messege[500];		//メッセージ：メッセージが存在する場合は画面にメッセージを表示する。
	char ans[10];		//答え
	int	item;			//アイテム：アイテム（鍵）がある場合はアイテムをを表示する。
	int	part;			//記憶のパーツ：パーツがある場合はアイテムをを表示する。
	int	room_num;

};

struct hero {	//主人公はデータ構造体

	int inventory_num;		//インベントリナンバー　：ゲットできた記憶のパーツやアイテムは順番に番号をつける。
							//char inventory[50];			//インベントリ　：プレイヤーキャラクターが持っているアイテムの一覧を表示する。
	int remember;			//主人公が持ってる記憶のパーツの数の表示
};

struct score {	//スコアはデータ構造

	int move_hero;		//主人公の移動回数の残り数の表示
	char part_hero;			//主人公が持ってる記憶のパーツの数の表示


};

struct room stage1[2000] = {	//部屋はデータ構造体


								/*　部屋の名前,　     問題　,　      ヒント　,　メッセージ,     答え　,　鍵の存在　,　記憶パーツ存在　,　部屋番号*/
								/*	"和室",     "何もありません。","　1991　","メッセージなし"," 4 ",       0 ,             0 ,             0,*/




	"和室","何もありません。","1991","メッセージなし","4",0,0,0,

	/**/	"和室","1+1=3, 1+0=2 ,1-1=2, 11+11=5, 11+12=4, 111+1111=? \n?になにがはいるでしょう。\n 選択: 1) 2 / 2) 1 / 3) 8 / 4) 知らん\n","1のみ","畳が八畳に敷かれている部屋だ。 とても心地よい場所だ、お祖母ちゃんの家って感じだ。 ","3",0,1,1,

	"階段","何もありません。\n","1991","この階段は2階に繋がっているようだ。 ","4",0,0,2,

	"キッチン","何もありません。\n","1991","コンロが5つもある。そんなに必要だろうか。 左から二つ目の元栓が緩んでいて、ガス漏れしそうだから止めとこう。","問",0,0,3,

	//"リビング","三本の線を足したとき最大で正方形の面の数はいくつか。\n            ■■■■■          \n         ■■■    ■■■        \n      ■■■          ■■■     \n    ■■■               ■■■  \n       ■                  ■  \n       ■                  ■  \n       ■                  ■  \n       ■                  ■  \n       ■                  ■  \n       ■                  ■  \n    ■■                ■■■  \n      ■■■          ■■■     \n         ■■■    ■■■■       \n            ■■■■■          \n","サイコロ","とても広く、シャンデリアや大きな天窓がある。 とても素敵だ。\n大きな天窓の形が0のような形をしていて、大空が綺麗に見えた。\n地球最後の時はこの空を黄昏たいな。\n外を眺めていたら何か思いだしそうだ。","女子大学",0,1,4,
	/**/	"リビング","六角形に三本の線を足したとき最大で正方形の面の数はいくつか。数字のみで答えよ\n            eeeee          \n         eee    eee        \n      eee          eee     \n    ee,               ee,  \n    e                  e5  \n    e                  e5  \n    e                  e5  \n    e                  e5  \n    e                  e5  \n    e                  e5  \n    ee                #eu  \n      eee          9ee     \n         eee    zeeu       \n            eeeey          \n選択: 1) 4 / 2) 6 / 3) 9 / 4) 7\n","サイコロ","とても広く、シャンデリアや大きな天窓がある。 とても素敵だ。\n大きな天窓の形が0のような形をしていて、大空が綺麗に見えた。\n地球最後の時はこの空を黄昏たいな。\n外を眺めていたら何か思いだしそうだ。","2",0,1,4,

	"トイレ","何もありません。","1991","タイルや金で出来ているトイレではなく普通の洋式トイレだった。カレンダーが貼ってあり、3日に赤丸がつけられてあった。3日のメモには5の右と書かれている","彼",0,0,5,

	/**/	"浴室","「EOE?EXN」 ? に入るものはなんでしょう。\n選択: 1) K / 2) X / 3) N / 4) R \n","数字が英語になっている(頭文字でない)","とても大きな浴槽だ。 \nモニターがついていて、テレビを見ながらお湯に浸かれそう。\nモニターにはローマ字でSHIORIと書いてある。\n人の名前だろうか。\n考えると頭に激痛がはしった。","4",0,1,6,

	"廊下","何もありません。","1991","豪邸なのか、とても広い廊下だ","4",0,0,7,

	"部屋","タンスを開けたら鍵をみつけた何かの鍵らしい。","1991","タンスが置いてある、何か見つかりそうだ。 ","4",1,0,8,

	/**/	"洗面台","正方形は何個あるんでしょうか？\neeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\ne         e        e         e        e\ne         e        e         e        e\ne         e   eeeeeeeeeee    e        e\ne         e   W    e    #    e        e\ne         e   W    e    #    e        e\neeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeze\ne         e   e    e    e    e        e\ne         e   W    e    #    e        e\ne         e   eeeeeeeeeee    e        e\ne         e        e         e        e\ne         e        e         e        e\neeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeze\ne         e        e         e        e\ne         e        e         e        e\ne         e   eeeeeeeeeee    e        e\ne         e   e    e    e    e        e\ne         e   e    e    e    e        e\neeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\ne         e   e    e    e    e        e\ne         e   e    e    e    e        e\ne         e   eeeeeeeeeee    e        e\ne         e        e         e        e\ne         e        e         e        e\neeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee \n選択: 1) 30 / 2) 40 / 3) 35 / 4) 36 \n","2×2, 3×3, 4×4","歯ブラシが一つ置いてあった。あかり以外住んでいないのだろう。鏡に映りこむボクを見ていると何か思い出しそうな気がする。 ","2",0,1,9,

	/**/	"玄関","この中に一つだけ間違いがある\nその問違いとは何でしょうか\n1  2  3  4  5\n  6  7  8  9\n  10  11  12\n(一文字で答えなさい）\n","数字は関係ない ","靴が2足ある。 \n男物と女物で、ボクの靴とあかりの靴だろうか。\nあかりは出かけたはずだけど、なんであるんだろう？\n何か思い出しそうだ。 ","問",0,1,10,

	"階段","何もありません。","1991","この階段は1階に繋がっているようだ。","4",0,0,11,

	"廊下","何もありません。","1991","いろいろな絵が飾られている。 \n有名な画家が描いたものであろうか。\nとても高そうだ。\n一番左には「3」と書かれただけのデッサンがあるが、\nこれは安そうだ。","4",0,0,12,

	/**/	"寝室","みんぎくんは世界一頭の良い男子高校生です。そのみんぎくんでも合格できなかった大学はどこでしょう。\n選択: 1) 女子大学 / 2) 東京大学 / 3) 東京工科大学 / 4) 宗教大学 \n","男が通えない","どこかで見かけたことのあるヘアピンをみつけた。 \n茜色の花がついていて、とてもかわいらしい。あかりの品物だろう。\nうっすらとあかりがヘアピンをつけているのを想像できた。\n大事なものなのかな…。\n頭に激痛がはしった。\n何か思い出しそうな気がする","1",0,1,13,

	/**/	"部屋2","1+3=6  1+4=5  4+2=4  3+5=2  2+5=? ?にはいるのはなんでしょう。\n 選択 1) 3 / 2) 2 / 3) 1 / 4) 9 \n","10","ここには一度\n訪れた気がする。","1",0,1,14,

	"部屋3","何もありません","1991","メッセージなし","6",0,0,15,

	"はしご","0","1991","","0",0,0,16,

	/**/ "倉庫","「あれ」は「帽子」,「聞ける」は「ペン」,「知る」は「今」,「座る」は「それ」,「彼女」は「？」 \n? にはいるものはなんでしょう。\n 選択: 1) 彼 / 2) これ / 3) 女の子 / 4) 空 \n","英語に直せ\n","部屋に入った瞬間鳥肌が立ってしまった。 \nとても暗いな。\nなにか暗らい所で赤をみた気する。\nあまりここにはいたくないな。","1",0,1,17,

	"屋根裏部屋","何もありません。","1991","","4",0,0,18,


	//"和室","何もありません。","1991","メッセージなし","4",0,0,0,

	//"和室","1+3=6  1+4=5\n4+2=4  3+5=2\n     2+5=?","1991","メッセージなし","3",0,1,1,
	//"階段","何もありません。","1991","メッセージなし","4",0,0,2,

	//	"台所","この中に一つだけ間違いがある\nその門違いとは何でしょうか？\n1  2  3  4  5\n  6  7  8  9\n  10  11  12\n","1991","メッセージなし","4",0,1,3,

	//"居室","よこたくんは世界一頭の良い男子高校生です\nそのよこたくんでも合格できなかった大学はどこでしょうか","1991","メッセージなし","4",0,1,4,

	//"トイレ","?には何が入るでしょ\n「あれ」は「帽子」　「聞ける」は「ペン」\n「知る」は「今」「座る」は「それ」\n「彼女」は「??」","1991","メッセージなし","4",0,1,5,

	//"溶室","1+1=?","1991","メッセージなし","2",0,1,6,

	//"廊下","なにもない","1991","メッセージなし","4",0,0,7,

	//"部屋","何もありません。","1991","メッセージなし","4",0,0,8,

	//"洗面","何もありません。","1991","メッセージなし","4",0,0,9,

	//"玄関","?に入る数字は？\n1+1=3\n1+0=2\n1-1=2\n11+11=5\n11+12=4\n111+1111=?\n","5+5","メッセージなし","10",0,1,10,

	//"階段","何もありません。","1991","メッセージなし","4",0,0,11,

	//"寝室","答えは4です。","1991","メッセージなし","4",0,0,12,

	//"部屋13","答えは4です。","1991","メッセージなし","4",0,1,13,

	//"部屋14","答えは4です。","1991","メッセージなし","4",0,0,14,

	//"部屋15","何もありません。","1991","メッセージなし","4",0,0,15,

	//"部屋16","鍵を発見しました。","1991","メッセージなし","4",1,0,16,

	//"部屋17","正方形はなんこあるんでしょう？\ne9eeeeeeeEe#eeeeee#e#eeeeeee9e9eeeeee9e\ne         e        e         e        e\ne         e        e         e        e\ne         e   DeEeXeXGG9e    e        e\ne         e   W    e    #    e        e\ne yyyyyyW e W,9yKW e yy e yy e yyyyyy e\ne WWWWWWK e W,95uW e WW e WW e WWWWWW e\ne         e   W    e    9    e        e\ne         e   De9Eye5EE#e    e        e\ne         e        e         e        e\ne         e        e         e        e\neDeeeeeeGzeXeeeeeeXeDeeeeeeezeDeeeeeeze\ne         e        e         e        e\ne         e        e         e        e\ne         e   WG##WeW#9zE  , e        e\ne         e   X    e    e    e        e\ne         e   u    e    9    e        e\nezeeeeeeezeDeEeeGeDeXeGDeDGGXeyGGGGGGDe\ne         e   K    e    #    e        #\ne         e   D    e    e    e        G\ne         e   ,GGeXeyEE9X    e        E\ne         e        e         e        9\ne uKKKKKu e KKKKKK e WWWWWWW e yyyyyWue\nuy5555555KWK555555WKKyy5y5yyuuuyyyy55yy","1991","メッセージなし","40",0,1,17,



};

struct room stage1_reset[2000] = {	//部屋はデータ構造体リセット





	"和室","何もありません。","1991","メッセージなし","4",0,0,0,

	/**/	"和室","1+1=3, 1+0=2 ,1-1=2, 11+11=5, 11+12=4, 111+1111=? \n?になにがはいるでしょう。\n 選択: 1) 2 / 2) 1 / 3) 8 / 4) 知らん\n","1のみ","畳が八畳に敷かれている部屋だ。 とても心地よい場所だ、お祖母ちゃんの家って感じだ。 ","3",0,1,1,

	"階段","何もありません。\n","1991","この階段は2階に繋がっているようだ。 ","4",0,0,2,

	"キッチン","何もありません。\n","1991","コンロが5つもある。そんなに必要だろうか。 左から二つ目の元栓が緩んでいて、ガス漏れしそうだから止めとこう。","問",0,0,3,

	//"リビング","三本の線を足したとき最大で正方形の面の数はいくつか。\n            ■■■■■          \n         ■■■    ■■■        \n      ■■■          ■■■     \n    ■■■               ■■■  \n       ■                  ■  \n       ■                  ■  \n       ■                  ■  \n       ■                  ■  \n       ■                  ■  \n       ■                  ■  \n    ■■                ■■■  \n      ■■■          ■■■     \n         ■■■    ■■■■       \n            ■■■■■          \n","サイコロ","とても広く、シャンデリアや大きな天窓がある。 とても素敵だ。\n大きな天窓の形が0のような形をしていて、大空が綺麗に見えた。\n地球最後の時はこの空を黄昏たいな。\n外を眺めていたら何か思いだしそうだ。","女子大学",0,1,4,
	/**/	"リビング","六角形に三本の線を足したとき最大で正方形の面の数はいくつか。数字のみで答えよ\n            eeeee          \n         eee    eee        \n      eee          eee     \n    ee,               ee,  \n    e                  e5  \n    e                  e5  \n    e                  e5  \n    e                  e5  \n    e                  e5  \n    e                  e5  \n    ee                #eu  \n      eee          9ee     \n         eee    zeeu       \n            eeeey          \n選択: 1) 4 / 2) 6 / 3) 9 / 4) 7\n","サイコロ","とても広く、シャンデリアや大きな天窓がある。 とても素敵だ。\n大きな天窓の形が0のような形をしていて、大空が綺麗に見えた。\n地球最後の時はこの空を黄昏たいな。\n外を眺めていたら何か思いだしそうだ。","2",0,1,4,

	"トイレ","何もありません。","1991","タイルや金で出来ているトイレではなく普通の洋式トイレだった。カレンダーが貼ってあり、3日に赤丸がつけられてあった。3日のメモには5の右と書かれている","彼",0,0,5,

	/**/	"浴室","「EOE?EXN」 ? に入るものはなんでしょう。\n選択: 1) K / 2) X / 3) N / 4) R \n","数字が英語になっている(頭文字でない)","とても大きな浴槽だ。 \nモニターがついていて、テレビを見ながらお湯に浸かれそう。\nモニターにはローマ字でSHIORIと書いてある。\n人の名前だろうか。\n考えると頭に激痛がはしった。","4",0,1,6,

	"廊下","何もありません。","1991","豪邸なのか、とても広い廊下だ","4",0,0,7,

	"部屋","タンスを開けたら鍵をみつけた何かの鍵らしい。","1991","タンスが置いてある、何か見つかりそうだ。 ","4",1,0,8,

	/**/	"洗面台","正方形は何個あるんでしょうか？\neeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\ne         e        e         e        e\ne         e        e         e        e\ne         e   eeeeeeeeeee    e        e\ne         e   W    e    #    e        e\ne         e   W    e    #    e        e\neeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeze\ne         e   e    e    e    e        e\ne         e   W    e    #    e        e\ne         e   eeeeeeeeeee    e        e\ne         e        e         e        e\ne         e        e         e        e\neeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeze\ne         e        e         e        e\ne         e        e         e        e\ne         e   eeeeeeeeeee    e        e\ne         e   e    e    e    e        e\ne         e   e    e    e    e        e\neeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\ne         e   e    e    e    e        e\ne         e   e    e    e    e        e\ne         e   eeeeeeeeeee    e        e\ne         e        e         e        e\ne         e        e         e        e\neeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee \n選択: 1) 30 / 2) 40 / 3) 35 / 4) 36 \n","2×2, 3×3, 4×4","歯ブラシが一つ置いてあった。あかり以外住んでいないのだろう。鏡に映りこむボクを見ていると何か思い出しそうな気がする。 ","2",0,1,9,

	/**/	"玄関","この中に一つだけ間違いがある\nその問違いとは何でしょうか\n1  2  3  4  5\n  6  7  8  9\n  10  11  12\n(一文字で答えなさい）\n","数字は関係ない","靴が2足ある。 \n男物と女物で、ボクの靴とあかりの靴だろうか。\nあかりは出かけたはずだけど、なんであるんだろう？\n何か思い出しそうだ。 ","問",0,1,10,

	"階段","何もありません。","1991","この階段は1階に繋がっているようだ。","4",0,0,11,

	"廊下","何もありません。","1991","いろいろな絵が飾られている。 \n有名な画家が描いたものであろうか。\nとても高そうだ。\n一番左には「3」と書かれただけのデッサンがあるが、\nこれは安そうだ。","4",0,0,12,

	/**/	"寝室","みんぎくんは世界一頭の良い男子高校生です。そのみんぎくんでも合格できなかった大学はどこでしょう。\n選択: 1) 女子大学 / 2) 東京大学 / 3) 東京工科大学 / 4) 宗教大学 \n","男が通えない","どこかで見かけたことのあるヘアピンをみつけた。 \n茜色の花がついていて、とてもかわいらしい。あかりの品物だろう。\nうっすらとあかりがヘアピンをつけているのを想像できた。\n大事なものなのかな…。\n頭に激痛がはしった。\n何か思い出しそうな気がする","1",0,1,13,

	/**/	"部屋2","1+3=6  1+4=5  4+2=4  3+5=2  2+5=? ?にはいるのはなんでしょう。\n 選択 1) 3 / 2) 2 / 3) 1 / 4) 9 \n","10","ここには一度\n訪れた気がする。","1",0,1,14,

	"部屋3","何もありません","1991","メッセージなし","6",0,0,15,

	"はしご","0","1991","","0",0,0,16,

	/**/ "倉庫","「あれ」は「帽子」,「聞ける」は「ペン」,「知る」は「今」,「座る」は「それ」,「彼女」は「？」 \n? にはいるものはなんでしょう。\n 選択: 1) 彼 / 2) これ / 3) 女の子 / 4) 空 \n","英語に直せ\n","部屋に入った瞬間鳥肌が立ってしまった。 \nとても暗いな。\nなにか暗らい所で赤をみた気する。\nあまりここにはいたくないな。","1",0,1,17,

	"屋根裏部屋","何もありません。","1991","","4",0,0,18,



};

struct hero katakura[50] = {	//主人公はデータ構造体

	0,0
};

struct hero katakura_reset[50] = {	//主人公はデータ構造体

	0,0
};

void map_reset();
void title();
void rule();
void prologue();

void story1();
void messege1();
void state();
void part_remem();
void slove();
void move_select();
void map1_dis();
void ending1();
void ending2();
void ending3();
void ending4();

void main() {

	system("mode con:cols=85 lines=50");
	map_reset();
	title();
	rule();
	prologue();

	story1();

	game = 1;
	while (game) {
		map1_dis();
		messege1();
		state();
		move_select();
		if (move < 0) {
			c = getchar();

		}
		printf("▼▽\n");
		c = getchar();
		system("cls");
		if (move == 0) {
			printf("------------------------------------------------------------\n");
			ending4();
			game = 0;
		}
	

		/*if (move <= 0 && (katakura[0].remember >= 0 && katakura[0].remember < 6)) {
			printf("------------------------------------------------------------\n");
			ending3();
			game = 0;
		}
		else if (move <= 0 && (katakura[0].remember > 5 && katakura[0].remember < 8)) {
			printf("------------------------------------------------------------\n");
			ending2();
			game = 0;
		}
		else if (move <= 0 && katakura[0].remember > 7) {
			printf("------------------------------------------------------------\n");
			ending1();
			game = 0;
		}*/

	}

	/*while (game) {
	map1_dis();
	messege1();
	state();
	move_select();
	c = getchar();
	system("cls");
	if (move <= 0) {
	void ending3();
	c = getchar();
	game = 0;
	}
	}
	*/
};

void map_reset() {

	memcpy(&stage1, &stage1_reset, sizeof(stage1_reset));
	//　mapの初期化,記憶のパーツの初期化
	//ゲームが始まるとマップ（屋敷）の構造体を初期化して謎（問題）、アイテム、メッセージなどの配置を初期化する。
	//　記憶のパーツの初期化
	//記憶のパーツの数を初期化し問題がある各部屋に１個ずつ分けて戻すため初期化する。
	//　クイズの初期化
	//問題を初期化し解けると記憶のパーツがゲットできるように初期化する。
	//　アイテムの初期化
	//アイテム（鍵、メッセージ）が元の位置に戻すため初期化する。
	memcpy(&katakura, &katakura_reset, sizeof(katakura_reset));
	//主人公の初期化
	//ゲームが始まると主人公は決めた位置とインベントリを初期化する。

	move = 10;
	//　移動回数の初期化
	//移動回数を１０個に初期化しプレイできるようにするため初期化する。

}

void title() {
	//　タイトルとルールを表示　
	//タイトルとルールを表示しプレイヤーにゲームを理解させる。
	printf("■        ■        ■   ■    ■   ■■■  ■■■■■  ■■■■\n");
	printf(" ■      ■■      ■    ■    ■     ■        ■      ■      \n");
	printf("  ■    ■  ■    ■     ■■■■     ■        ■      ■■■■\n");
	printf("   ■  ■    ■  ■      ■    ■     ■        ■      ■      \n");
	printf("    ■■      ■■       ■    ■     ■        ■      ■      \n");
	printf("     ■        ■        ■    ■   ■■■      ■      ■■■■\n\n");
	printf("　　　■     ■     ■      ■■■   ■■■   ■■■■\n");
	printf("　　　■■   ■   ■  ■      ■    ■    ■  ■      \n");
	printf("　　　■ ■  ■ ■      ■    ■     ■       ■■■■\n");
	printf("　　　■  ■ ■ ■      ■    ■       ■■   ■      \n");
	printf("　　　■   ■■   ■  ■      ■    ■    ■  ■      \n");
	printf("　　　■     ■     ■      ■■■    ■■■  ■■■■\n\n");
	printf("\n");
	printf("Press enter key.");
	c = getchar();
	system("cls");
}



void rule() {		//Prologueの表示
					//ゲームのストーリーや世界観とゲームの現在の状況をプレイヤーに理解させるためPrologueを表示する。
	printf("☆★ルールの説明★☆\n\n");
	printf("1.物語の舞台となる屋敷の中には『記憶のカケラ』が8つ隠されており、この『記憶のカケラ』を”できる限り多く”発見することが、このゲームの目的である。\n\n");
	printf("2.『探索』というコマンドが存在するが、このコマンドを怪しい場所で実行する事により、その場所における『イベント』が発生する。『探索』コマンドの使用回数は『10回』までなので、計画的に使うべし。\n\n");
	printf("3.『記憶のカケラ』は『イベント』の一つである『問題』を発見し、それに正解する事で手に入る。\n\n");
	printf("4.『問題』を解く際『探索』コマンドを使用する事により、『ヒント』を見ることもできる。どうしても問題が解けない時に活用すべし。\n\n");
	printf("5.『問題』は一度間違えると消滅してしまい、再挑戦は出来ない。\n\n");
	printf("6.『寝室（X）』『廊下（X）』と言う文字はマップを、『(◯)』マークはプレイヤーを表す。例えば、『寝室（◯）』となっている場合、プレイヤーが寝室に居る事を意味する。\n\n");
	printf("7.ゲーム内の重要アイテムである『鍵』を入手した場合、それ以降プレイヤーを示すアイコンは『◯』から『●』に変化する。\n\n");
	printf("8.ゲーム終了までに集めた『記憶のカケラ』の個数により、エンディングが変化する。時間に余裕があれば、ぜひ再挑戦して、より良いエンディングを目指そう。\n\n");

	/*printf("☆★ルールの説明★☆\n\n");
	printf("10の大切な事\n");
	printf("1.常にMAPが表示され、○はプレイヤーの位置を表す。\n");
	printf("2.探索回数が制限され、[探索]のコマンドを選択すると必然的に探索回数が減る。\n");
	printf("3.探索回数は12回とする。\n");
	printf("4.〇が表示されていて、アイテムである鍵を入手すると●へと変化する。\n");
	printf("5.記憶の欠片を最大で8つ入手しなければならない。\n");
	printf("6.記憶の欠片はある特定の場所を探索時に問題が現れ、解くことができたら入手とする。　また、ヒントを使用する場合、[探索]をしたとみなされ、探索回数が減る。\n");
	printf("7.問題の解答を間違えると一つ前の部屋にもどる。問題は解き直せるが探索しなければならない。\n");
	printf("8.ストーリーを楽しめ。\n");
	printf("9.記憶の欠片の数に応じて、シナリオ変化。\n");
	printf("10.何度も挑戦して、すべてのシナリオを探せ！\n\n");*/

	printf("◆◇コマンド◇◆\n\n");
	printf("1.ENTER / 次のページ\n");
	printf("2.移動 / 数字\n");
	printf("3.選択　　　 / タイピング\n");
	printf("Enter..>>");
	c = getchar();
	system("cls");

}

void prologue() {		//Prologueの表示
						//ゲームのストーリーや世界観とゲームの現在の状況をプレイヤーに理解させるためPrologueを表示する。

	printf("▼プロローグ▼\n\n");
	printf("夢を見ていた気がする。\n\n");
	printf("とても、とても大切だった誰かの笑顔。声。温もり。綺麗な黒い髪。\n\n");
	printf("その髪に光る白いヘアピンはボクが誕生日に贈ったモノだ。\n\n");
	printf("とても暖かくて、かけがいのないモノだったはずなのに、\n\n");
	printf("それらはボクの体を通り抜け、どこか遠くへ行ってしまう気がして、\n\n");
	printf("ひどく不安な気持ちになる…\n\n");
	printf("Enter..>>");
	c = getchar();
	system("cls");
}

/*void pig() {
//printf("名前は３文字以内にしてください。\n");
printf("名前を設定ください。\n");
printf("あなたの名前は？\n");
printf("名前：");
scanf("%s", &name);
system("cls");

}*/

void story1() {
	printf("あきら「…うぅ…ん？」\n"); c = getchar();
	printf("あきら「ここは一体…　そもそもどうして…　グッ…！」\n"); c = getchar();
	printf("見知らぬ部屋で目が覚めた。\n"); c = getchar();
	printf("今までのことを思い出そうとするが、それを邪魔するかのように記憶にホワイトノイズがかかり、頭に激痛が走った。\n"); c = getchar();
	printf("思わず頭を抱えようと腕を動かすと、ふと、右手にほんのりと誰かの体温を感じた。\n"); c = getchar();
	printf("体温を感じるほうに目をやると、そこにはボクの手を大切そうに握りながら、スースーと寝息をたてて寝ている少女がいた。\n"); c = getchar();
	printf("あきら「この子、どこかで…」\n"); c = getchar();
	printf("記憶を探ろうとするも、やはり頭に激痛が奔る。\n"); c = getchar();
	printf("ボクが起きた事に気づいたのか目の前の少女が飛び起きた。\n"); c = getchar();
	printf("？？？「よかった……！　目が覚めたのね！？」\n"); c = getchar();
	printf("少女は安堵と歓喜の入り混じった声をあげ。\n"); c = getchar();
	printf("？？？「すっごく心配したんだよ！？　ねえちょっと！　私がどれだけ心配したかわかってる！？ 」\n"); c = getchar();
	printf("ボクのことを心配してくれていたらしい少女は、状況が分からずにボケッとしているボクの表情を見て、頬を膨らませている。\n"); c = getchar();
	printf("あきら「……えっとゴメン、キミは誰？」\n"); c = getchar();
	printf("？？？「え……？」\n"); c = getchar();
	printf("少女は驚きの声をあげる。\n"); c = getchar();
	printf("？？？「わたしのこと……覚えてないの……？」\n"); c = getchar();
	printf("彼女はそう言うが、思い出せないものは思い出せない。\n"); c = getchar();
	printf("あきら「ごめん、本当に何も思い出せないんだ…」\n"); c = getchar();
	printf("あきら「もちろん、キミのことも…」\n"); c = getchar();
	printf("あきら「あ、あの、よければ名前をきいてもいいかな…？」\n"); c = getchar();
	printf("あかり「あ、うん。私の名前はあかり。……一応、キミの『彼女』なんだよ？」\n"); c = getchar();
	printf("少女の名前は『アカリ』と言うらしい。\n"); c = getchar();
	printf("あきら「あかりさん、心配かけてゴメン」\n"); c = getchar();
	printf("あきら「看病までしてもらったみたいなのに、キミのことを忘れてしまうなんて……」\n"); c = getchar();
	printf("あきら「……それと、ありがとう」\n"); c = getchar();
	printf("あかり「えへへ……。はい、どういたしまして！」\n"); c = getchar();
	printf("あきら「えっと、もう一つだけ聞きたいんだけど、ここはどこ？」\n"); c = getchar();
	printf("あかり「ここ？ ここは私とキミのお家だよ？ ああそっか、全部忘れちゃってるんだよね。」\n"); c = getchar();
	printf("あかり「うーん、まだまだ色々と聞きたいことはあると思うんだけど……」\n"); c = getchar();
	printf("彼女はそう言いながら立ち上がった。\n"); c = getchar();
	printf("あかり「ゴメン！ 私、ちょっと用事があるからお出かけしないといけないんだよね」\n"); c = getchar();
	printf("あきら「え、出かけるの……？」\n"); c = getchar();
	printf("正直なところ、まだ一人になるのは少し不安だったのだが、ずっと看病してくれた彼女がわざわざ出かけるほどなのだ、きっと大切な用事なのだろう。\n"); c = getchar();
	printf("あきら「うん、わかった。いってらっしゃい」\n"); c = getchar();
	printf("あかり「うん！　行ってきまーす！」\n"); c = getchar();
	printf("あかりはバタバタと支度をすると、不安そうなボクを安心させるように、一度こちらに笑いかけてから出かけていった。\n"); c = getchar();
	printf("あきら「うーん。せっかく起きたのに何もしないってのは少し退屈だな…」\n"); c = getchar();
	printf("あきら「そうだ。少し家の中を探検してみよう。何か思い出すきっかけが見つかるかも知れない」\n"); c = getchar();
	printf("ボクはベッドから起き上がり、一度伸びをすると、家の探索を始めることにした。\n"); c = getchar();
	printf("NEXT>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"); c = getchar();
	system("cls");
}



void map1_dis() {

	char map[20];
	int map_num;
	for (map_num = 0; map_num < 20; map_num++) {		 //現在地を'.'であらわす。
		if (stage1[i].room_num == map_num) {
			map[map_num] = 'O';
		}
		else if (stage1[i].room_num != map_num) {		//現在地以外は' 'であらわす。
			map[map_num] = 'X';
		}
	}
	printf("            M          A            P\n");
	printf("1F\n");
	printf("                               [ 和室 (%c) ]        \n", map[1]);
	printf("[ 階段 (%c) ][ キッチン (%c)  ][     リビ (%c)     ][ トイレ (%c) ][　浴 (%c) ]\n", map[2], map[3], map[4], map[5], map[6]);
	printf("[ 廊下 (%c) ][    部屋  (%c)  ][     　ング       ][ 洗面台 (%c) ][  室     ]\n", map[7], map[8], map[9]);
	printf("[ 玄関 (%c) ]\n", map[10]);
	printf("------------------------------------------------------------------------------\n");
	printf("2F\n");
	printf("      [階段 (%c) ]\n", map[11]);
	printf("[               廊下 (%c)         ][  寝(%c) ]\n", map[12], map[13]);
	printf("[      部屋2 (%c)   ][ 部屋3 (%c)  ][  屋    ]\n", map[14], map[15]);
	printf("[      はしご(%c)   ][ 倉庫 (%c)  ]                              [????(%c)]\n", map[16], map[17], map[18]);
	printf("-----------------------------------------------------------------------------\n");
}

void messege1() {
	//　メッセージの表示
	//主人公が一番始めてもらうアイテムでもあり今後なにをすべきかがわかるよう話を表示する。

	printf("※メッセージ※\n%s\n", stage1[i].messege);
	c = getchar();

}



void state() {
	//現在の位置や状態の表示
	//現在の位置と持ってるアイテム、選択可能なCommandを表示する。
	printf("      ----------------------\n");
	printf("     l 現在位置：%s       l\n", stage1[i].room_name);

	if (katakura[0].inventory_num == 0) {
		printf("     l 鍵：○               l\n");
	}
	else if (katakura[0].inventory_num == 1) {
		printf("     l 鍵：●               l\n");
	}
	printf("     l 記憶のパーツ：%d      l\n", katakura[0].remember);

	printf("     l 探索回数：%d         l\n", move);
	printf("      ----------------------", move);
	printf("\n");



}


void slove() {
	//謎解き
	//プレイヤーの画面に問題が現れ答えを選択し問題を解く。

	strcpy_s(ans1, sizeof("0"), "0");

	/*printf("%s", &ans1);*/

	hint1 = 0;

	int j;
	/*printf("%d\n", stage1[i].part);*/
	if (stage1[i].part == 1) {

		printf(">>問題<<\n%s\n", stage1[i].question);

		printf("ヒントを見ますか？\n");
		printf("1.みる　2.みない\n");
		while (!(hint1 == 1 || hint1 == 2)) {
			hint1 = 0;
			printf("選択：");
			scanf_s("%d", &hint1);

			//printf("%d\n", ans1);
			//printf("%d\n", stage1[i].ans);
			if (hint1 == 1) {
				move--;
				printf("%s\n", stage1[i].hint);


			}
			/*else if (hint1 != 1 && hint1 != 2) {

			}
			*/
		}

		while (!strcmp(ans1, "0")) {
			printf("\n");
			printf("答えを入力してください。\n");
			printf("答え：");
			scanf_s("%s", &ans1, sizeof(ans1));
			//printf("%d\n", ans1);
			//printf("%d\n", stage1[i].ans);


			if (!strcmp(ans1, stage1[i].ans)) {
				printf("\n");
				printf("正解です。\n");
				//記憶のパーツを手に入れる　
				//謎の問題を解いて記憶のパーツを取得し、アイテム構造体から
				//データをプレイヤーキャラクター（主人公）のデータに移動させる。
				//	if (stage1[i].part == 1) {
				stage1[i].part = 0;

				

				katakura[0].remember++;
				/*printf("%d\n", stage1[i].part);*/
				printf("記憶のパーツを拾った。\n\n");
				//}else if (stage1[i].part == 0) {
				//	printf("記憶の破片がない。\n");
				//}
				
				strcpy_s(stage1[i].question, sizeof("0"), "0");
				
				move_select();

			}

			else {
				printf("[%s]は不正解です。\n", &ans1, sizeof(ans1));
				printf("↓NEXT↓\n");
				
				c = getchar();
				strcpy_s(stage1[i].question, sizeof("0"), "0");
				/*		printf("前の部屋に帰った。\n");
				i = p_i;  */


			}

		}


	}
	else if (stage1[i].item == 1) {
		printf("%s\n", stage1[i].question);


		//if (stage1[i].item == 1) {
		stage1[i].item = 0;
		katakura[0].inventory_num++;
		printf("鍵を拾った。\n");
		//}
		//else if (stage1[i].part == 0) {
		//	printf("記憶の破片がない。\n");
		//}
		strcpy_s(stage1[i].question, sizeof("0"), "0");
		move_select();

	}
	/*else if(stage1[i].item == 0){
				move_select1 = 0;
		// printf("何もなかったので移動する。\n");
		printf("移動しますか？\n");
		printf("1.移動 \n");
		printf("選択：");
		scanf_s("%d", &move_select1);
		printf("\n");*/



	else {
		printf("%s\n", stage1[i].question);

		move_select();
	}


}

void move_select() {
	
	if (move == 1) {
		
		printf("警告：探索可能な回数が後残り１回です。\n");
		printf("ヒント：はしごの方に何かがあるかも\n\n");
		
	}

	if (katakura[0].remember == 8) {
		printf("全て思い出した。\n");
		printf("はしごに向かってみよう。\n\n");
	}

	if (i == 18) {
		p_i = i;
		printf("屋根裏部屋のようだ\n"); c = getchar();
		printf("....???\n"); c = getchar();
		system("cls");
		if (katakura[0].remember >= 0 && katakura[0].remember < 6) {

			printf("------------------------------------------------------------\n");
			ending3();
			game = 0;
		}
		else if (katakura[0].remember >6 && katakura[0].remember < 8) {
			printf("------------------------------------------------------------\n");
			ending2();
			game = 0;
		}
		else if (katakura[0].remember > 7) {
			printf("------------------------------------------------------------\n");
			ending1();
			game = 0;
		}
	}
	else if (!strcmp(stage1[i].question, "0")) {
		move_select1 = 0;
		// printf("何もなかったので移動する。\n");
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("移動しますか？\n");
		printf("1.移動 \n");
		printf("選択：");
		scanf_s("%d", &move_select1);
		printf("\n");

		if (move_select1 == 1) {
			p_i = i;

			if (i == 1) {
			
				printf("どこに移動しますか？\n");
				printf("1.リビング\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 4;
				}
				else {
					printf("部屋じゃない。\n");
				}
			}

			//11111111111111111111111111111111111111111111111

			else if (i == 2) {
				p_i = i;
			
				printf("どこに移動しますか？\n");
				printf("1.２階に上がる // 2.廊下\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 11;
				}
				else if (dir_select == 2) {

					i = 7;
				}
				else {
					printf("部屋じゃない。\n");
				}
			}

			//22222222222222222222222222222222222222222

			else if (i == 3) {
				p_i = i;
				
				printf("どこに移動しますか？\n");
				printf("1.リビング\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 4;
				}

				else {
					printf("部屋じゃない。\n");
				}
			}

			//3333333333333333333333333333333333333333333

			else if (i == 4) {
				p_i = i;
			
				printf("どこに移動しますか？\n");
				printf("1.キッチン // 2.部屋 // 3.トイレ // 4.洗面台 // 5.和室\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 3;
				}
				else if (dir_select == 2) {

					i = 8;
				}
				else if (dir_select == 3) {

					i = 5;
				}
				else if (dir_select == 4) {

					i = 9;
				}
				else if (dir_select == 5) {

					i = 1;
				}
				else {
					printf("部屋じゃない。\n");
				}
			}

			//444444444444444444444444444444444444444444444444444

			else if (i == 5) {
				p_i = i;
				
				printf("どこに移動しますか？\n");
				printf("1.リビング \n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 4;
				}

				else {
					printf("部屋じゃない。\n");
				}

			}
			//555555555555555555555555555555555555555555555555555555555555

			else if (i == 6) {
				p_i = i;
				
				printf("どこに移動しますか？\n");
				printf("1.洗面台 \n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 9;
				}

				else {
					printf("部屋じゃない。\n");
				}
			}
			//666666666666666666666666666666666666666666666666666666666666666666
			else if (i == 7) {
				p_i = i;
			
				printf("どこに移動しますか？\n");
				printf("1.階段に上がる // 2.玄関 // 3.部屋\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 12;
				}
				else if (dir_select == 2) {

					i = 10;
				}
				else if (dir_select == 3) {

					i = 8;
				}
				else {
					printf("部屋じゃない。\n");
				}
			}
			//777777777777777777777777777777777777777777777777777777777777777
			else if (i == 8) {
				p_i = i;
			
				printf("どこに移動しますか？\n");
				printf("1.廊下 // 2.リビング\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 7;
				}
				else if (dir_select == 2) {

					i = 4;
				}

				else {
					printf("部屋じゃない。\n");
				}
			}
			//888888888888888888888888888888888888888888888888888

			else if (i == 9) {
				p_i = i;
			
				printf("どこに移動しますか？\n");
				printf("1.リビング // 2.浴室 \n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 4;
				}
				else if (dir_select == 2) {

					i = 6;
				}

				else {
					printf("部屋じゃない。\n");
				}
			}
			//9999999999999999999999999999999999999999999999999999999999
			else if (i == 10) {

				p_i = i;
				
				printf("どこに移動しますか？\n");
				printf("1.廊下\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 7;
				}
				else {
					printf("部屋じゃない。\n");
				}
			}
			//101010101110101010110101010110101010110101010
			else if (i == 11) {
				p_i = i;
			
				printf("どこに移動しますか？\n");
				printf("1.一階に降りる // 2.廊下\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 7;
				}
				else if (dir_select == 2) {

					i = 12;
				}

				else {
					printf("部屋じゃない。\n");
				}
			}
			//111111111111111111111111111111111111111111111111111111111

			else if (i == 12) {
				p_i = i;
			
				printf("どこに移動しますか？\n");
				printf("1.階段を降りる // 2.部屋2 // 3.部屋3 // 4.寝室\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 7;
				}
				else if (dir_select == 2) {

					i = 14;
				}
				else if (dir_select == 3) {

					i = 15;
				}
				else if (dir_select == 4) {

					i = 13;
				}

				else {
					printf("部屋じゃない。\n");
				}
			}

			//12121212121212121212121212121212121212121212121

			else if (i == 13) {
				p_i = i;
		
				printf("どこに移動しますか？\n");
				printf("1.廊下 \n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 12;
				}

				else {
					printf("部屋じゃない。\n");
				}
			}
			//13131331313131313131313131313131313131313131313131313

			else if (i == 14) {
				p_i = i;
			
				printf("どこに移動しますか？\n");
				printf("1.廊下 // 2.はしご\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 12;
				}

				else if (dir_select == 2) {



					printf("扉が閉まっている。\n");
					if (katakura[0].inventory_num == 1) {
						printf("鍵を持っています。\n");
						printf("扉を開けます。\n");


						i = 16;
					}


					//3
					else if (katakura[0].inventory_num == 0) {
						printf("鍵を持っていない。\n");
						printf("扉を開けません。\n");
						i = 14;
					}



				}
			}
			//14141414141414141414141414141414141414141414141414141414141414141414

			/*else if (i == 15) {
			p_i = i;
			printf("部屋15\n");
			printf("どこに移動しますか？\n");
			printf("1.↑廊下↑ // 2.↓部屋17↓\n");
			scanf_s("%d", &dir_select);
			if (dir_select == 1) {

			i = 12;
			}
			else if (dir_select == 2) {



			i = 17;


			}

			else {
			printf("部屋じゃない。\n");
			}
			}
			*/
			//151515151515151515151515151515151515151515151515151515

			else if (i == 15) {
				p_i = i;
			
				printf("どこに移動しますか？\n");
				printf("1.廊下 // 2.倉庫\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 12;
				}
				else if (dir_select == 2) {
					printf("\n");
					printf("暗証番号がわからないと倉庫へはいけないらしい。\n");
					printf("番号入力：");
					scanf_s("%d", &pass);
					if (pass == 3530) {
						//if (pass == 3530 && katakura[0].inventory_num == 1) {

						printf("ドアが開いた。\n");
						i = 17;
					}
					else {

						printf("暗証番号が間違ったようだ。");
						i = 15;

					}

				}
			}

			else if (i == 16) {
				p_i = i;
		
				printf("どこに移動しますか？\n");
				printf("1.部屋2　// 2.????\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 14;
				}
				else if (dir_select == 2) {

					i = 18;
				}
				else {
					printf("部屋じゃない。\n");
				}
			}

			//171717171717171717171717171717171717171717

			else if (i == 17) {
				p_i = i;
			
				printf("どこに移動しますか？\n");
				printf("1.部屋3 \n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 15;
				}

				else {
					printf("部屋じゃない。\n");
				}
			}

			c = getchar();

		}

	}
	else {
		move_select1 = 0;
		printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		printf("移動しますか？\n");
		printf("1.移動 2.探索\n");
		printf("選択：");
		scanf_s("%d", &move_select1);
		printf("\n");

		if (move_select1 == 1) {
			p_i = i;

			if (i == 1) {
		
				printf("どこに移動しますか？\n");
				printf("1.リビング\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 4;
				}
				else {
					printf("部屋じゃない。\n");
				}
			}

			//11111111111111111111111111111111111111111111111

			else if (i == 2) {
				p_i = i;
			
				printf("どこに移動しますか？\n");
				printf("1.２階に上がる // 2.廊下\n");
				printf("選択：");
				scanf_s("%d", &dir_select);

				if (dir_select == 1) {

					i = 11;
				}
				else if (dir_select == 2) {

					i = 7;
				}
				else {
					printf("部屋じゃない。\n");
				}
			}

			//22222222222222222222222222222222222222222

			else if (i == 3) {
				p_i = i;
			
				printf("どこに移動しますか？\n");
				printf("1.リビング\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 4;
				}

				else {
					printf("部屋じゃない。\n");
				}
			}

			//3333333333333333333333333333333333333333333

			else if (i == 4) {
				p_i = i;
				
				printf("どこに移動しますか？\n");
				printf("1.キッチン // 2.部屋 // 3.トイレ // 4.洗面台 // 5.和室\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 3;
				}
				else if (dir_select == 2) {

					i = 8;
				}
				else if (dir_select == 3) {

					i = 5;
				}
				else if (dir_select == 4) {

					i = 9;
				}
				else if (dir_select == 5) {

					i = 1;
				}
				else {
					printf("部屋じゃない。\n");
				}
			}

			//444444444444444444444444444444444444444444444444444

			else if (i == 5) {
				p_i = i;
				
				printf("どこに移動しますか？\n");
				printf("1.リビング \n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 4;
				}

				else {
					printf("部屋じゃない。\n");
				}

			}
			//555555555555555555555555555555555555555555555555555555555555

			else if (i == 6) {
				p_i = i;
			
				printf("どこに移動しますか？\n");
				printf("1.洗面台 \n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 9;
				}

				else {
					printf("部屋じゃない。\n");
				}
			}
			//666666666666666666666666666666666666666666666666666666666666666666
			else if (i == 7) {
				p_i = i;
			
				printf("どこに移動しますか？\n");
				printf("1.階段を上がる // 2.玄関 // 3.部屋\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 12;
				}
				else if (dir_select == 2) {

					i = 10;
				}
				else if (dir_select == 3) {

					i = 8;
				}
				else {
					printf("部屋じゃない。\n");
				}
			}
			//777777777777777777777777777777777777777777777777777777777777777
			else if (i == 8) {
				p_i = i;
				
				printf("どこに移動しますか？\n");
				printf("1.廊下 // 2.リビング\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 7;
				}
				else if (dir_select == 2) {

					i = 4;
				}

				else {
					printf("部屋じゃない。\n");
				}
			}
			//888888888888888888888888888888888888888888888888888

			else if (i == 9) {
				p_i = i;
			
				printf("どこに移動しますか？\n");
				printf("1.リビング // 2.浴室 \n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 4;
				}
				else if (dir_select == 2) {

					i = 6;
				}

				else {
					printf("部屋じゃない。\n");
				}
			}
			//9999999999999999999999999999999999999999999999999999999999
			else if (i == 10) {
			
				printf("どこに移動しますか？\n");
				printf("1.廊下\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 7;
				}
				else {
					printf("部屋じゃない。\n");
				}
			}
			//101010101110101010110101010110101010110101010
			else if (i == 11) {
				p_i = i;
			
				printf("どこに移動しますか？\n");
				printf("1.一階に降りる // 2.廊下\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 7;
				}
				else if (dir_select == 2) {

					i = 12;
				}

				else {
					printf("部屋じゃない。\n");
				}
			}
			//111111111111111111111111111111111111111111111111111111111

			else if (i == 12) {
				p_i = i;
			
				printf("どこに移動しますか？\n");
				printf("1.階段を降りる // 2.部屋2 // 3.部屋3 // 4.寝室\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 7;
				}
				else if (dir_select == 2) {

					i = 14;
				}
				else if (dir_select == 3) {

					i = 15;
				}
				else if (dir_select == 4) {

					i = 13;
				}

				else {
					printf("部屋じゃない。\n");
				}
			}

			//12121212121212121212121212121212121212121212121

			else if (i == 13) {
				p_i = i;
			
				printf("どこに移動しますか？\n");
				printf("1.廊下 \n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 12;
				}

				else {
					printf("部屋じゃない。\n");
				}
			}
			//13131331313131313131313131313131313131313131313131313

			else if (i == 14) {
				p_i = i;
			
				printf("どこに移動しますか？\n");
				printf("1.廊下 // 2.はしご\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 12;
				}

				else if (dir_select == 2) {



					printf("扉が閉まっている。\n");
					if (katakura[0].inventory_num == 1) {
						printf("鍵を持っています。\n");
						printf("扉を開けます。\n");


						i = 16;
						
					}


					//3
					else if (katakura[0].inventory_num == 0) {
						printf("鍵を持っていない。\n");
						printf("扉を開けません。\n");
						i = 14;
					}



				}
			}
			//14141414141414141414141414141414141414141414141414141414141414141414

			/*else if (i == 15) {
			p_i = i;
			printf("部屋15\n");
			printf("どこに移動しますか？\n");
			printf("1.↑廊下↑ // 2.↓部屋17↓\n");
			scanf_s("%d", &dir_select);
			if (dir_select == 1) {

			i = 12;
			}
			else if (dir_select == 2) {



			i = 17;


			}

			else {
			printf("部屋じゃない。\n");
			}
			}
			*/
			//151515151515151515151515151515151515151515151515151515

			else if (i == 15) {
				p_i = i;
		
				printf("どこに移動しますか？\n");
				printf("1.廊下 // 2.倉庫\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 12;
				}
				else if (dir_select == 2) {
					printf("暗証番号がわからないと倉庫へはいけないらしい。\n");
					printf("番号入力：");
					scanf_s("%d", &pass);
					if (pass == 3530) {
						//if (pass == 3530 && katakura[0].inventory_num == 1) {

						printf("ドアが開いた。\n");
						i = 17;
					}
					else {

						printf("暗証番号が間違ったようだ。");
						i = 15;

					}

				}
			}

			else if (i == 16) {
				p_i = i;
	
				printf("どこに移動しますか？\n");
				printf("1.部屋2　// 2.????\n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 14;
				}
				else if (dir_select == 2) {

					i = 18;
				}
				else {
					printf("部屋じゃない。\n");
				}
			}

			//171717171717171717171717171717171717171717

			else if (i == 17) {
				p_i = i;
				
				printf("どこに移動しますか？\n");
				printf("1.部屋3 \n");
				printf("選択：");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 15;
				}

				else {
					printf("部屋じゃない。\n");
				}
			}

			c = getchar();

		}

		else if (move_select1 == 2) {

			move--;
			slove();


		}
	}
	//	c = getchar();

}


void ending1() {
	printf("その部屋は異様に静かで、どことなく不気味な雰囲気を漂わせていた。\n"); c = getchar();
	printf("明るい寝室に慣れていたボクの目には、その薄暗い部屋の中はシルエットくらいにしか見えなかった。\n"); c = getchar();
	printf("目を凝らすと黒い人影のようなものが見えた。\n"); c = getchar();
	printf("ボクは壁に手を探るようにして、屋根裏部屋の電気のスイッチを探した。\n"); c = getchar();
	printf("電気を付けると、そこには少女が椅子に縛れていた。\n"); c = getchar();
	printf("ボクは反射的に助けなければならない衝動に駆られた。\n"); c = getchar();
	printf("少女は気を失っているのか倒れるようにして座っている。\n"); c = getchar();
	printf("身体を揺すり起こそうとすると、\n"); c = getchar();
	printf("あきら「朱莉、朱莉、朱莉！！」\n"); c = getchar();
	printf("ボクはなぜか涙を流しなら「朱莉」と何度も呼びかけ起こそうとしていた。\n"); c = getchar();
	printf("なんで泣いているのかわからない。\n"); c = getchar();
	printf("始めてあったはずの人なのに。\n"); c = getchar();
	printf("胸を締め付けるように苦しい。\n"); c = getchar();
	printf("涙が止まらない。\n"); c = getchar();
	printf("あきら「朱莉、朱莉、朱莉！！！！！　起きてくれよ！！　朱莉！！」\n"); c = getchar();
	printf("ボクは必至に朱莉を呼びながら身体をゆすっていた。\n"); c = getchar();
	printf("朱莉「そんなに何度も呼ばれなくたって聞こえてるよ」\n"); c = getchar();
	printf("朱莉は朦朧した状態でボクを心配させないように声を掛けてくれたのだ。\n"); c = getchar();
	printf("ボクは身体の全員の力が抜けてしまい床に座り込んでしまった。\n"); c = getchar();
	printf("あきら「よかった、よかったよ」\n"); c = getchar();
	printf("すべて忘れていたのに、いつの間にか記憶も思い出してしていた。\n"); c = getchar();
	printf("そうか、詩織。\n"); c = getchar();
	printf("ごめんな。\n"); c = getchar();
	printf("（過去）--------------------------------------------------------------------------------------------------------------\n"); c = getchar();
	printf("朱莉とは高校の時の後輩と先輩の部活の関係であった。\n"); c = getchar();
	printf("ボクの名前は空(あきら)、テニス部に所属していた。\n"); c = getchar();
	printf("テニス部では全国を目指すほど強くはなかったが、しっかり練習を行い大会ではそこそこ上位に入賞していた。\n"); c = getchar();
	printf("ボクは小さいころからテニスをやっていたので、そこそこ強く副部長を任せられていた。中でもずば抜けて強かったのがボクの彼女朱莉であり、部活のキャプテンを任されていたほどの実力者。元気で明るく、天真爛漫でみんなを引っ張ってくれる存在だ。\n"); c = getchar();
	printf("明るすぎて眩しい存在で、ボクにはもったいない。\n"); c = getchar();
	printf("朱莉とは幼稚園からの幼馴染で 昔からの付き合い、小さいころから遊ぶ時や学校に行くときは家が近所だという理由で一緒にいる事が多かった。\n"); c = getchar();
	printf("ボクのどこが好きになってくれたのかわからないが、中学を卒業とともに告白をされ、返事をする暇なく、\n"); c = getchar();
	printf("朱莉「いいよね？これからもよろしくねっ！」\n"); c = getchar();
	printf("と無理やり付き合う感じになったが、ボクはとてもうれしかったことを覚えている。\n"); c = getchar();
	printf("それからボクらは同じ高校に入り、テニス部で活動していくうち、高学年で部長と副部長となった。\n"); c = getchar();
	printf("高学年となるとともに新入生がテニス部に入ってきた。その新入生の一人が詩織であった。\n"); c = getchar();
	printf("詩織は物静かであまり話さないのが特徴で、同じ新入生と親しんでる様子はなく、朱莉とは正反対の性格だ。\n"); c = getchar();
	printf("静かである故か試合となるととても冷静で計算高く、相手のスキを狙うプレイを得意としていた。\n"); c = getchar();
	printf("なかなかみんなの輪に入ろうとしない詩織を見かねた朱莉は性格上無視できなく、学食や遊びに行くときに無理やり誘い、笑って過ごせる空間を作ったのだ。\n"); c = getchar();
	printf("そんな日が当たり前になってきた頃、ボクは詩織に相談に乗ってほしいと呼ばれた。\n"); c = getchar();
	printf("相談の内容は自分自身を変えたいという内容で、「どうしたら朱莉のようになれますか？」と質問され、ボクは「今のままでいいんじゃないかな？」と至極単純に答えたのだ。\n"); c = getchar();
	printf("詩織は「そうですか」と一言いうと、二言目に「空が大好きです」と答えたのだ。\n"); c = getchar();
	printf("ボクは一瞬、頭が真っ白になってしまったが、冷静になり「ごめんね」といった。\n"); c = getchar();
	printf("詩織はその瞬間「今のままでは空とは付き合えないのですね」と一言のこし、去っていった。\n"); c = getchar();
	printf("次の日見掛けると、いつもは物静かであったのが無理して元気に 振舞っている詩織の姿があった。\n"); c = getchar();
	printf("その姿をみたボクはすぐに気が付き、朱莉の真似ごとをしていることがわかった。\n"); c = getchar();
	printf("朱莉は少し明るくなったのかな程度で気づいていなかったが、ボクは申し訳なく気づかないふりをしたのだ。\n"); c = getchar();
	printf("それから日が立ち、ボクたちは卒業したのだ。\n"); c = getchar();
	printf("式が終わった後でボクと朱莉の前に詩織が来て、\n"); c = getchar();
	printf("詩織「大変お世話になりましたっ！、本当にありがとうございましたっ！」\n"); c = getchar();
	printf("と感謝の言葉を掛けてくれたのだ。\n"); c = getchar();
	printf("詩織はお世話になった分をお返ししたいということで、家に招かれた。\n"); c = getchar();
	printf("詩織は資産家の娘で別荘をもっているらしく、別荘に三人で行くことになったのだ。\n"); c = getchar();
	printf("ボクたちは別荘に向かうことになった。\n"); c = getchar();
	printf("別荘は森の中を少し進んだ所にあり、森に囲まれた豪華な家が佇んでいた。\n"); c = getchar();
	printf("中に入ると、玄関には大きなキャンバスが飾ってあり、芸術家の描いたような\n"); c = getchar();
	printf("鮮やかな色合いの花が飾られていた。\n"); c = getchar();
	printf("詩織「先輩方、気楽にあがってくださいっ！」\n"); c = getchar();
	printf("と元気な声でボクらを迎えてくれた。\n"); c = getchar();
	printf("朱莉「おじゃまします、この家にはだれも住んでないの？」\n"); c = getchar();
	printf("玄関を見た感じボクたちの靴しかなく、他には誰もいないと思ったが、こんなにも広い家にボクたちだけなのが信じられなかった。\n"); c = getchar();
	printf("一人暮らしにはもったいないくらい豪華な家。さすがに資産家の娘だ。\n"); c = getchar();
	printf("詩織「そうですね、この家は私が自立するためだけに建てられたので、だれもいないですよっ！」\n"); c = getchar();
	printf("朱莉「そういえばこの家で何をするの？」朱莉はサプライズをしてもらえると思ったのかわざとらしく伝えた。\n"); c = getchar();
	printf("ボクたちは何も知らされていない状態で、詩織に連れて来られていたのだ。\n"); c = getchar();
	printf("わざわざ別荘に来たんだから、盛大なことなんだろうか。\n"); c = getchar();
	printf("詩織「まだ秘密ですっ！」\n"); c = getchar();
	printf("詩織はサプライズをしたいのか、どこか心をウキウキさせている気持ちを漂わせていた。\n"); c = getchar();
	printf("詩織「今から2階に行きます、2階から屋根裏部屋に繋がっていて、案外部屋の中が広いんですよっ！」\n"); c = getchar();
	printf("朱莉「いいねっ！、はやくいこぉー！」\n"); c = getchar();
	printf("朱莉は子供みたいにはしゃいでいる。\n"); c = getchar();
	printf("ボクも少しは屋根裏部屋なんてアニメみたいで、少し興味がある。\n"); c = getchar();
	printf("屋敷の部屋にはいろいろなインテリアが飾られていて、一つ一つとても高そうだ。\n"); c = getchar();
	printf("ボクらは1階から2階にあがった。屋根裏部屋に繋がる階段は、別のところにあるらしい。\n"); c = getchar();
	printf("詩織「こっちですっ！」\n"); c = getchar();
	printf("ボクらは詩織の言うままに通路を歩き、寝室らしき部屋に入った。\n"); c = getchar();
	printf("屋根裏部屋につながる部屋らしく、天井は一見真っ白であるが隅に小さな穴があった。\n"); c = getchar();
	printf("詩織は鍵を取り出した。どうやら屋根裏部屋に入るには鍵が必要らしい。\n"); c = getchar();
	printf("「先輩、この鍵で開けてさきにはいっていてくださいっ！、飲み物取り入ってくるのでっ！」\n"); c = getchar();
	printf("詩織はボクたちに鍵を渡し、飲み物を取りってしまった。\n"); c = getchar();
	printf("朱莉「言われた通りに先に入ろうかっ！」\n"); c = getchar();
	printf("詩織は受け取った鍵で鍵穴に入れ回すと天井の一部が捲れて、その中から、ハシゴが出てきた。\n"); c = getchar();
	printf("中が気になって早く入りたい〇〇〇は先にはしごを上り、ボクも後から入っていった。\n"); c = getchar();
	printf("部屋の中は異様に静かで、どことなく不気味な雰囲気を漂わせていた。\n"); c = getchar();
	printf("薄暗い部屋の中を恐る恐る進みと、\n"); c = getchar();
	printf("詩織「卒業おめでとうございますっ！」\n"); c = getchar();
	printf("『パァーン！！！』の音と同時に薄暗い部屋から、光が飛んできて、目がくらんでしまった。\n"); c = getchar();
	printf("それは電気の明かりによるものであり、目が慣れ見渡してみると、そこには詩織が撃った後のクラッカーを持っていた。\n"); c = getchar();
	printf("朱莉「びっくりしたぁー！　心臓に悪いよ！！！　もぅ！」\n"); c = getchar();
	printf("朱莉とボクはとても驚いたが、すぐに冷静になった。\n"); c = getchar();
	printf("詩織「脅かせてすみません！　サプライズだったもので！」\n"); c = getchar();
	printf("詩織「飲み物を持ってきたので乾杯しましょう！！」\n"); c = getchar();
	printf("詩織はとてもご機嫌な様子でうれしそうだ。その様子をみているこっちもなんだかうれしい。\n"); c = getchar();
	printf("詩織「では先輩達の卒業を祝って！　カンパーイ！！」\n"); c = getchar();
	printf("詩織はそれぞれに飲み物を用意してくれ、一緒に乾杯をして飲んだ。\n"); c = getchar();
	printf("ボクたちは部活動や一緒に遊んだことを三人で語り、盛大に盛り上がった。\n"); c = getchar();
	printf("すると、次第に身体が重くなってくるのを感じた。\n"); c = getchar();
	printf("お酒が入っているのか、頭が朦朧とし始めたのだ。\n"); c = getchar();
	printf("空「詩織、飲み物にお酒をいれたのかぁ・・？」\n"); c = getchar();
	printf("ボクは詩織に質問したが返事は帰ってこなく、薄気味悪く笑っていたのだ。\n"); c = getchar();
	printf("朱莉の方を見ると朱莉はいつの間にか床で倒れて死んだように眠っていたのだ。\n"); c = getchar();
	printf("直感的に危機を感じて助けなければならないと感じた。\n"); c = getchar();
	printf("空「朱莉・・・」\n"); c = getchar();
	printf("朱莉を起こさなければならないと思い名前を呼んだが、なんで朱莉と呼んだのかわからなくなってしまった。\n"); c = getchar();
	printf("だんだん頭の中が空っぽになる感覚となり、今までの思い出一つ一つにホワイトノイズが掛かった。\n"); c = getchar();
	printf("ボクは頭で何も考えられなくなった。\n"); c = getchar();
	printf("「なんで？」「どうして？」「なぜ？」「夢？」「？？？」「ああああああああああああああああああああああああああああああああああ」\n"); c = getchar();
	printf("何もかも・・・。\n"); c = getchar();
	printf("空「ボクは誰？」\n"); c = getchar();
	printf("（現実）\n"); c = getchar();
	printf("明るく振舞っていた詩織が静かに後ろに立っていた。\n"); c = getchar();
	printf("空「詩織、ボクのせいだよな」\n"); c = getchar();
	printf("ボクの事を好きな詩織の気持ちをわからないふりをしてしまっていたのだ。\n"); c = getchar();
	printf("朱莉はなぜこの状況になっているのかをわかってはいなかった。\n"); c = getchar();
	printf("詩織「私はあなたを大好きだった」\n"); c = getchar();
	printf("詩織「がんばって先輩(朱莉)の真似をして明るく見せて、少しでも振り向いてほしかった」\n"); c = getchar();
	printf("詩織「どんなに努力したって私は報われなかった」\n"); c = getchar();
	printf("詩織「真似事だってわかっていても少しでも近づいて、あなたの隣にいたかった」\n"); c = getchar();
	printf("詩織がボクに振り向いてもらうと頑張っているのは痛いほど伝わっていたのだ。\n"); c = getchar();
	printf("それを無視していた報いだったのか。\n"); c = getchar();
	printf("朱莉「詩織ちゃん、そうだったのね」\n"); c = getchar();
	printf("朱莉「私全然気づかなくて、空の事が好きだったんだね」\n"); c = getchar();
	printf("朱莉「でもごめんね」\n"); c = getchar();
	printf("朱莉「私は詩織ちゃんがどれだけ想っていても、渡す気はないよ」\n"); c = getchar();
	printf("朱莉「それだけ好き！」\n"); c = getchar();
	printf("いつもは全然好きとか言ってくれなかったが、朱莉はボクを心底愛してくれていることを伝えてくれ、ボクは決意した。\n"); c = getchar();
	printf("空「詩織、ごめんな」\n"); c = getchar();
	printf("空「ボクは朱莉が好きなんだ、好きなのは性格だけじゃないし小さい時から一緒にいろんな思い出を作ってきて、築き上げてきたから、ボクは朱莉しか愛せないんだ。」\n"); c = getchar();
	printf("空「しっかり伝えなくてごめんな」\n"); c = getchar();
	printf("空「朱莉のすべてが好きでだから、どんなに似てようが関係ない」\n"); c = getchar();
	printf("空「今まで一緒にいた時間が朱莉と作ってきたものが、簡単には崩れない」\n"); c = getchar();
	printf("空「だから詩織にも、一緒に築き上げれるパートナーを探してほしい」\n"); c = getchar();
	printf("空「性格は大事だけど、それがすべてじゃないってわかっているはずだよね？」\n"); c = getchar();
	printf("空「だから、ボクは詩織のことを愛せない」\n"); c = getchar();
	printf("ボクは心の隅にたまっていたものをさらけ出してすべてを伝えた。\n"); c = getchar();
	printf("詩織「わかっています」\n"); c = getchar();
	printf("詩織「実際に朱莉さんとなって先輩(空)に接していましたが、私を好きにはなってくれないだなと感じてしまいました」\n"); c = getchar();
	printf("詩織「薬を飲み物にいれて、記憶をなくさせてしまいました・・・」\n"); c = getchar();
	printf("詩織「本当にごめんなさい」\n"); c = getchar();
	printf("詩織は泣きながらすべてを告白してくれたのだ。\n"); c = getchar();
	printf("ボクの事を愛し、朱莉の真似をし、詩織はすべて無駄だったと感じただろうか。\n"); c = getchar();
	printf("ボクはそうは思わない、失敗して得られた経験は人生の中で素晴らしいものだから。\n"); c = getchar();
	printf("詩織には新しい未来に進んでほしいと願った。\n"); c = getchar();
	printf("朱莉「大丈夫だよ、結局何もなかったんだから！」\n"); c = getchar();
	printf("朱莉はこんな事をされても平気な顔で詩織をフォローしたのだ。\n"); c = getchar();
	printf("尋常でないような事が実際にあったのに、怒りが湧くことはなかったのだ。\n"); c = getchar();
	printf("詩織は本当だったらボクたちを殺したかったのだろう。\n"); c = getchar();
	printf("たとえそうであったとしても、ボクたちは詩織という一人の人間を否定しない。\n"); c = getchar();
	printf("Happy END\n"); c = getchar();

	system("cls");

}


void ending2() {

	printf("...?\n"); c = getchar();
	printf("その部屋は異様に静かで、どことなく不気味な雰囲気を漂わせていた。\n"); c = getchar();
	printf("明るい寝室に慣れ切っていたボクの目には、その薄暗い部屋の中はシルエットくらいにしか視えなかった。\n"); c = getchar();
	printf("しかし、その様な些細な印象を一瞬で塗りつぶす圧倒的な違和感に、ボクの全神経は釘付けになった。\n"); c = getchar();
	printf("屋根裏部屋は、強烈な匂いに満ちていた。\n"); c = getchar();

	printf("あまりの臭いに吐き気を抑えきれず、ボクはとっさに口元を抑える。\n"); c = getchar();
	printf("空「――ウッ！　おえっ…！」　\n"); c = getchar();
	printf("ソレは、平凡に生きている人間は、おそらく一生嗅ぐことの無いであろう強烈な臭いだった。\n"); c = getchar();
	printf("当然ボクもこんな臭いを嗅ぐのは初めてだ。\n"); c = getchar();
	printf("しかし、本能的に直感する。\n"); c = getchar();
	printf("これは、死んだ生き物の臭いだ。\n"); c = getchar();
	printf("この部屋には生き物の死体がある。\n"); c = getchar();
	printf("そんな直感に、心が折れそうになる。\n"); c = getchar();
	printf("そして、畳み掛けるように、最悪のタイミングで部屋の暗さに目が慣れ始めた。\n"); c = getchar();
	printf("徐々に明らかになっていくその光景は、「こうだったらイヤだな」　とボクが想像したモノを、そのままそっくり投影したかのような、まるで現実感の無いものだった。\n"); c = getchar();
	printf("床に、壁に、家具に、まるでバケツに入ったペンキをぶち撒けたかの様に、赤黒い染みや模様がこびりついていた。\n"); c = getchar();

	printf("血だ。\n"); c = getchar();

	printf("おびただしい量のそれらは、持ち主の体からこぼれ落ちて随分経つのだろう。赤黒く変色し、ベットリと部屋全体にこびりついていた。\n"); c = getchar();

	printf("（探索後クローゼットを見つけて開く）\n"); c = getchar();
	printf("あきら「ひっ…！」\n"); c = getchar();
	printf("クローゼットの中には、地獄が詰まっていた。\n"); c = getchar();
	printf("部屋に漂っていた腐臭を何倍にも凝縮したような、あまりにも濃い死の匂い。\n"); c = getchar();
	printf("血の海、飛び散る肉片、醜く蠢く無数の蛆虫。\n"); c = getchar();
	printf("地獄の釜の中身をそのままぶち撒けた様な、酷く凄惨なその光景の中に、一人の少女の死体が横たわっていた。\n"); c = getchar();
	printf("苦しみに見開かれた目。開ききった瞳孔。口と鼻からは血が流れ、手足は力なく垂れ下がっている。服は元の色が分からない程に血に染まり、その体には見えるものだけでも軽く十を超える切り傷と刺し傷が刻まれていた。\n"); c = getchar();
	printf("その凄惨に過ぎる光景からは、犯人のねばつくような悪意と、殺された少女の地獄の様な苦しみが、直接ボクの心に流れ込んでくるようで、見ているだけで心が壊れてしまいそうだ。\n"); c = getchar();
	printf("しかし、ボクはなぜかその少女の死体から、目を離すことができなかった。\n"); c = getchar();
	printf("血に濡れた少女の顔を見る。\n"); c = getchar();
	printf("ふと、死んでいるはずの少女と目が合った気がした。\n"); c = getchar();
	printf("瞬間。\n"); c = getchar();
	printf("締め切られていたカーテンを一気に開いたように、記憶の暗かった場所全てに光が当たり、ボクは、全てを思い出した。\n"); c = getchar();
	printf("「ずっと一人でこんな暗いところに…。　寂しかったよな。　痛かったよな。　忘れてごめんな…。『あかり』…！」\n"); c = getchar();
	printf("どんな時でも笑顔だった太陽のような彼女。\n"); c = getchar();
	printf("出会った時からずっと変わらず、ボクのことを 『キミ』 と呼ぶ彼女。\n"); c = getchar();
	printf("誕生日にプレゼントしたひまわりのヘアピンを、嬉しそうにいつも付けていた彼女。\n"); c = getchar();
	printf("その細い体を、切れ味の悪そうなフルーツナイフで何度も何度も突き刺されながら、自分の方がよっぽど痛いだろうに、苦しいだろうに、そんな状況で、情けなくも動けなくなったボクの事を心配そうに見つめていた彼女。\n"); c = getchar();

	printf("そんな彼女のことを、あんなに大好きだった、大切だった彼女のことを、あろうことか完全に忘れていた、愚かで情けない自分に対して、怒りが湧き上がる。\n"); c = getchar();
	printf("そして、許せない人間はもう一人いた。\n"); c = getchar();
	printf("「お前は…。　お前のことだけは絶対に許さない…！」\n"); c = getchar();
	printf("	深い怒りと憎しみを込めて、忘れていたその名前を呟く。\n"); c = getchar();
	printf("「許さないぞ…。　『詩織』…！」\n"); c = getchar();

	printf("「全部思い出してしまいましたか…。　残念です『先輩』」\n"); c = getchar();

	printf("振り返ると、そこには悪魔が立っていた。\n"); c = getchar();
	printf("あかりを殺し、ボクの記憶を奪い、あろうことか『あかり』に成り代わろうとした、悪魔のようなあの女が、『詩織』が、細い三日月のような、気持ちの悪い笑みをその顔に貼り付けながら、静かに立っていた。\n"); c = getchar();
	printf("何も考えていなかった。\n"); c = getchar();
	printf("目の前に立っている詩織が何をしてこようがどうでもいい。\n"); c = getchar();
	printf("ただただ詩織を恨んで怨んで殺したくて、何もできなかったボクはグズでのろまで死んでもいい。\n"); c = getchar();
	printf("もう終わってもいい。すべてなくなってしまえばいいのに。\n"); c = getchar();

	printf("ずさっ！！\n"); c = getchar();

	printf("何か刺さったのか、自分の血が流れてくるのが見えた。\n"); c = getchar();
	printf("これで、朱莉と同じになれた。\n"); c = getchar();
	printf("ボクは少し笑みを浮かべながら御経のように唱えていた。\n"); c = getchar();
	printf("死ね死ね死ね死ね死ね死ね・・・・。\n"); c = getchar();
	printf("ギュっ！！\n"); c = getchar();
	printf("ボクは詩織の顔をまじかに見た瞬間反射的に詩織の首を片手で締め付けた。\n"); c = getchar();
	printf("詩織は抵抗しようと刃物で体を斬りつけてくるが、痛くない。\n"); c = getchar();
	printf("別に強がっているわけじゃない、どうでもいい・・・。\n"); c = getchar();
	printf("「はやく死ねばいいのに」\n"); c = getchar();
	printf("いつの間にか詩織の反抗は止んでいた。\n"); c = getchar();
	printf("ボクは首を絞めている手を放した。\n"); c = getchar();
	printf("息ができなくて死んでいた。\n"); c = getchar();
	printf("いつのまにか詩織の顔や身体に痣ができ、血が流れていた。\n"); c = getchar();
	printf("気づかないうちに空いている片手で殴っていたのだろう。\n"); c = getchar();
	printf("覚えていないがどうでもいい。\n"); c = getchar();
	printf("死んでろ。\n"); c = getchar();
	printf("バタンッ！！\n"); c = getchar();
	printf("ボクの倒れた先は空いたクローゼットの目の前だった。\n"); c = getchar();
	printf("最後の力を振り絞り、体を引きずりながらボクは朱莉のばにいてやれた。\n"); c = getchar();
	printf("...\n"); c = getchar();
	printf("<<<<<<<<<<<<<準エンディング>>>>>>>>>>>>\n"); c = getchar();
	system("cls");
}


void ending3() {
	printf("その部屋は異様に静かで、どことなく不気味な雰囲気を漂わせていた。\n"); c = getchar();
	printf("明るい寝室に慣れていたボクの目には、その薄暗い部屋の中はシルエットくらいにしか視えなかった。\n"); c = getchar();
	printf("しかし、その様な些細な印象を一瞬で塗りつぶす圧倒的な違和感に、ボクの全神経は釘付けになった。\n"); c = getchar();

	printf("――腐臭だ。\n"); c = getchar();

	printf("あまりの臭いに吐き気を抑えきれず、ボクはとっさに手で口を抑える。\n"); c = getchar();
	printf("あきら「――ウッ！　おえっ…！」　\n"); c = getchar();
	printf("ソレは平凡に生きている人間は一生嗅ぐことの無いであろう強烈な臭いだった。\n"); c = getchar();
	printf("当然ボクもこんな臭いを嗅ぐのは初めてだ。\n"); c = getchar();
	printf("しかし、本能的に直感する。\n"); c = getchar();
	printf("これは、生き物が死んだ臭い。　\n"); c = getchar();
	printf("死臭だ。\n"); c = getchar();
	printf("そして、畳み掛けるように、最悪のタイミングで部屋の暗さに目が慣れ始めた。\n"); c = getchar();
	printf("徐々に明らかになったその光景は、部屋に満ちる腐臭から、「こうだったらイヤだな」と想像した光景をそのまま投影したかのような、まるで現実感の無いものだった。\n"); c = getchar();
	printf("床に、壁に、家具に、まるでバケツに入ったペンキをぶち撒けたかの様に、赤黒い染みや模様がこびりついていた。\n"); c = getchar();

	printf("血だ。\n"); c = getchar();

	printf("おびただしい量のそれらは、持ち主の体からこぼれ落ちて随分経つのだろう。赤黒く変色し、ベットリと部屋全体にこびりついていた。\n"); c = getchar();

	printf("あきら「あ…　あぁ…」\n"); c = getchar();
	printf("あまりの惨状を前に全身の力が抜け、その場にへたり込んでしまった。\n"); c = getchar();
	printf("頭が真っ白になる。\n"); c = getchar();
	printf("ボクはどうしてこんな恐ろしいところに居るんだろう。\n"); c = getchar();
	printf("逃げなければ。\n"); c = getchar();
	printf("この恐ろしい屋敷から。彼女から。そしてこの得体の知れない記憶の残骸から。\n"); c = getchar();
	printf("回らない頭で、動かない体で、それでもとにかく逃げなければと、気力を振り絞り立ち上がる。\n"); c = getchar();
	printf("立てた。まだ彼女は帰っていない。今のうちに逃げよう。\n"); c = getchar();
	printf("「ダメだよ」\n"); c = getchar();

	printf("咄嗟に思い出したのは、小さい頃、少し大きなハチに腕を刺された時の、あの感覚だった。\n"); c = getchar();
	printf("なんとも言えないイヤな熱さ。体内に熱した何かをねじ込まれたような、耐え難い気持ち悪さ。\n"); c = getchar();
	printf("背中を中心に、体はとても熱いのに、頭の中はスッと冷たくなる、妙な感覚。　直後。\n"); c = getchar();

	printf("激痛。\n"); c = getchar();

	printf("あきら「ぐあッ！？　ぐっ！！？　ぐぅぅぅッ！！！！」\n"); c = getchar();
	printf("――痛い痛いイタイイタイイタイいたいいたい\n"); c = getchar();
	printf("背中に何かが刺さった？　刺された？　誰に？　なんで？\n"); c = getchar();

	printf("あまりの激痛のうずくまり、転げ回る。\n"); c = getchar();
	printf("視界と頭は暴走し、加熱し、激しく明滅する。\n"); c = getchar();
	printf("「キ、キミはッ…！　どうし…て…　なん…で……」\n"); c = getchar();
	printf("赤く塗りつぶされていく視界の端で、アカリが人形の様な無表情でボクを見下ろしていた。\n"); c = getchar();
	printf("その目は壊れた玩具を眺める子供のような、無機質で空虚なモノだった。\n"); c = getchar();
	printf("赤く染まりきったボクの視界は、その部屋で殺されたであろう誰かの血と同じように、徐々に黒くなってゆき、やがて最初から何も無かったかの様に、ただただ真っ黒に染まった。\n"); c = getchar();
	printf("\n");
	printf("記憶を取り戻すことはできなかった。\n"); c = getchar();
	printf("<<<<<<<<<<<<<バットエンディング>>>>>>>>>>>>\n"); c = getchar();

	system("cls");

}


void ending4() {

	printf("あかりが帰ってきた、玄関の音が聞こえた。\n"); c = getchar();
	printf("玄関に迎えに行こう。\n"); c = getchar();
	printf("あかり「ただいま！」\n"); c = getchar();
	printf("あきら「おかえり」\n"); c = getchar();
	printf("あかり「いっぱい食材買ってきたよっ！」\n"); c = getchar();
	printf("あかり「今日の晩御飯は君が好きだったハンバーグっ！」\n"); c = getchar();
	printf("ボクは何も思い出せないがハンバーグが好きだったんだな。\n"); c = getchar();
	printf("あきら「手伝うよ」\n"); c = getchar();
	printf("あかり「ありがと〜！」\n"); c = getchar();
	printf("あれから、三年。いまだ記憶は戻らないが楽しい生活に馴染んでいる。\n"); c = getchar();
	printf("あかりとは結婚して、子供を作ろうと考えている。\n"); c = getchar();
	printf("誰か大事な人を忘れているような気がするが、気のせいだろう。\n"); c = getchar();
	printf("<<<<<<<<<<<<<エンディング>>>>>>>>>>>>\n"); c = getchar();
	system("cls");

}
