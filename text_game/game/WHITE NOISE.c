#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int win_1;				//��������
int win_2;				//��������2
int lose;				//�s�k����
int move;				//�ړ��񐔂̐���
int present;			//���݂̈ʒu
char c;					//enter�p
char ans1[10];			//�����p
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


struct room {	//�����̓f�[�^�\����

	char room_name[50];		//���݂̈ʒu�F���݈ʒu�͕����ŕ\���B�e�������Ƃɖ��O������܂��B
	char question[5000];		//��̖��F�䂪�����ꍇ�A��̖�����ʂɕ\������B
	char hint[50];			//�q���g�F�q���g��I�������ꍇ�͖��Ɋ֘A����q���g��\������B
	char messege[500];		//���b�Z�[�W�F���b�Z�[�W�����݂���ꍇ�͉�ʂɃ��b�Z�[�W��\������B
	char ans[10];		//����
	int	item;			//�A�C�e���F�A�C�e���i���j������ꍇ�̓A�C�e������\������B
	int	part;			//�L���̃p�[�c�F�p�[�c������ꍇ�̓A�C�e������\������B
	int	room_num;

};

struct hero {	//��l���̓f�[�^�\����

	int inventory_num;		//�C���x���g���i���o�[�@�F�Q�b�g�ł����L���̃p�[�c��A�C�e���͏��Ԃɔԍ�������B
							//char inventory[50];			//�C���x���g���@�F�v���C���[�L�����N�^�[�������Ă���A�C�e���̈ꗗ��\������B
	int remember;			//��l���������Ă�L���̃p�[�c�̐��̕\��
};

struct score {	//�X�R�A�̓f�[�^�\��

	int move_hero;		//��l���̈ړ��񐔂̎c�萔�̕\��
	char part_hero;			//��l���������Ă�L���̃p�[�c�̐��̕\��


};

struct room stage1[2000] = {	//�����̓f�[�^�\����


								/*�@�����̖��O,�@     ���@,�@      �q���g�@,�@���b�Z�[�W,     �����@,�@���̑��݁@,�@�L���p�[�c���݁@,�@�����ԍ�*/
								/*	"�a��",     "��������܂���B","�@1991�@","���b�Z�[�W�Ȃ�"," 4 ",       0 ,             0 ,             0,*/




	"�a��","��������܂���B","1991","���b�Z�[�W�Ȃ�","4",0,0,0,

	/**/	"�a��","1+1=3, 1+0=2 ,1-1=2, 11+11=5, 11+12=4, 111+1111=? \n?�ɂȂɂ��͂���ł��傤�B\n �I��: 1) 2 / 2) 1 / 3) 8 / 4) �m���\n","1�̂�","�􂪔���ɕ~����Ă��镔�����B �ƂĂ��S�n�悢�ꏊ���A���c�ꂿ���̉Ƃ��Ċ������B ","3",0,1,1,

	"�K�i","��������܂���B\n","1991","���̊K�i��2�K�Ɍq�����Ă���悤���B ","4",0,0,2,

	"�L�b�`��","��������܂���B\n","1991","�R������5������B����ȂɕK�v���낤���B �������ڂ̌������ɂ�ł��āA�K�X�R�ꂵ����������~�߂Ƃ����B","��",0,0,3,

	//"���r���O","�O�{�̐��𑫂����Ƃ��ő�Ő����`�̖ʂ̐��͂������B\n            ����������          \n         ������    ������        \n      ������          ������     \n    ������               ������  \n       ��                  ��  \n       ��                  ��  \n       ��                  ��  \n       ��                  ��  \n       ��                  ��  \n       ��                  ��  \n    ����                ������  \n      ������          ������     \n         ������    ��������       \n            ����������          \n","�T�C�R��","�ƂĂ��L���A�V�����f���A��傫�ȓV��������B �ƂĂ��f�G���B\n�傫�ȓV���̌`��0�̂悤�Ȍ`�����Ă��āA����Y��Ɍ������B\n�n���Ō�̎��͂��̋�����������ȁB\n�O�𒭂߂Ă����牽���v�������������B","���q��w",0,1,4,
	/**/	"���r���O","�Z�p�`�ɎO�{�̐��𑫂����Ƃ��ő�Ő����`�̖ʂ̐��͂������B�����݂̂œ�����\n            eeeee          \n         eee    eee        \n      eee          eee     \n    ee,               ee,  \n    e                  e5  \n    e                  e5  \n    e                  e5  \n    e                  e5  \n    e                  e5  \n    e                  e5  \n    ee                #eu  \n      eee          9ee     \n         eee    zeeu       \n            eeeey          \n�I��: 1) 4 / 2) 6 / 3) 9 / 4) 7\n","�T�C�R��","�ƂĂ��L���A�V�����f���A��傫�ȓV��������B �ƂĂ��f�G���B\n�傫�ȓV���̌`��0�̂悤�Ȍ`�����Ă��āA����Y��Ɍ������B\n�n���Ō�̎��͂��̋�����������ȁB\n�O�𒭂߂Ă����牽���v�������������B","2",0,1,4,

	"�g�C��","��������܂���B","1991","�^�C������ŏo���Ă���g�C���ł͂Ȃ����ʂ̗m���g�C���������B�J�����_�[���\���Ă���A3���ɐԊۂ������Ă������B3���̃����ɂ�5�̉E�Ə�����Ă���","��",0,0,5,

	/**/	"����","�uEOE?EXN�v ? �ɓ�����̂͂Ȃ�ł��傤�B\n�I��: 1) K / 2) X / 3) N / 4) R \n","�������p��ɂȂ��Ă���(�������łȂ�)","�ƂĂ��傫�ȗ������B \n���j�^�[�����Ă��āA�e���r�����Ȃ��炨���ɐZ���ꂻ���B\n���j�^�[�ɂ̓��[�}����SHIORI�Ə����Ă���B\n�l�̖��O���낤���B\n�l����Ɠ��Ɍ��ɂ��͂������B","4",0,1,6,

	"�L��","��������܂���B","1991","���@�Ȃ̂��A�ƂĂ��L���L����","4",0,0,7,

	"����","�^���X���J�����献���݂��������̌��炵���B","1991","�^���X���u���Ă���A���������肻�����B ","4",1,0,8,

	/**/	"���ʑ�","�����`�͉������ł��傤���H\neeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\ne         e        e         e        e\ne         e        e         e        e\ne         e   eeeeeeeeeee    e        e\ne         e   W    e    #    e        e\ne         e   W    e    #    e        e\neeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeze\ne         e   e    e    e    e        e\ne         e   W    e    #    e        e\ne         e   eeeeeeeeeee    e        e\ne         e        e         e        e\ne         e        e         e        e\neeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeze\ne         e        e         e        e\ne         e        e         e        e\ne         e   eeeeeeeeeee    e        e\ne         e   e    e    e    e        e\ne         e   e    e    e    e        e\neeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\ne         e   e    e    e    e        e\ne         e   e    e    e    e        e\ne         e   eeeeeeeeeee    e        e\ne         e        e         e        e\ne         e        e         e        e\neeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee \n�I��: 1) 30 / 2) 40 / 3) 35 / 4) 36 \n","2�~2, 3�~3, 4�~4","���u���V����u���Ă������B������ȊO�Z��ł��Ȃ��̂��낤�B���ɉf�肱�ރ{�N�����Ă���Ɖ����v���o�������ȋC������B ","2",0,1,9,

	/**/	"����","���̒��Ɉ�����ԈႢ������\n���̖�Ⴂ�Ƃ͉��ł��傤��\n1  2  3  4  5\n  6  7  8  9\n  10  11  12\n(�ꕶ���œ����Ȃ����j\n","�����͊֌W�Ȃ� ","�C��2������B \n�j���Ə����ŁA�{�N�̌C�Ƃ�����̌C���낤���B\n������͏o�������͂������ǁA�Ȃ�ł���񂾂낤�H\n�����v���o���������B ","��",0,1,10,

	"�K�i","��������܂���B","1991","���̊K�i��1�K�Ɍq�����Ă���悤���B","4",0,0,11,

	"�L��","��������܂���B","1991","���낢��ȊG�������Ă���B \n�L���ȉ�Ƃ��`�������̂ł��낤���B\n�ƂĂ����������B\n��ԍ��ɂ́u3�v�Ə����ꂽ�����̃f�b�T�������邪�A\n����͈��������B","4",0,0,12,

	/**/	"�Q��","�݂񂬂���͐��E�ꓪ�̗ǂ��j�q���Z���ł��B���݂̂񂬂���ł����i�ł��Ȃ�������w�͂ǂ��ł��傤�B\n�I��: 1) ���q��w / 2) ������w / 3) �����H�ȑ�w / 4) �@����w \n","�j���ʂ��Ȃ�","�ǂ����Ō����������Ƃ̂���w�A�s�����݂����B \n���F�̉Ԃ����Ă��āA�ƂĂ����킢�炵���B������̕i�����낤�B\n��������Ƃ����肪�w�A�s�������Ă���̂�z���ł����B\n�厖�Ȃ��̂Ȃ̂��ȁc�B\n���Ɍ��ɂ��͂������B\n�����v���o�������ȋC������","1",0,1,13,

	/**/	"����2","1+3=6  1+4=5  4+2=4  3+5=2  2+5=? ?�ɂ͂���̂͂Ȃ�ł��傤�B\n �I�� 1) 3 / 2) 2 / 3) 1 / 4) 9 \n","10","�����ɂ͈�x\n�K�ꂽ�C������B","1",0,1,14,

	"����3","��������܂���","1991","���b�Z�[�W�Ȃ�","6",0,0,15,

	"�͂���","0","1991","","0",0,0,16,

	/**/ "�q��","�u����v�́u�X�q�v,�u������v�́u�y���v,�u�m��v�́u���v,�u����v�́u����v,�u�ޏ��v�́u�H�v \n? �ɂ͂�����̂͂Ȃ�ł��傤�B\n �I��: 1) �� / 2) ���� / 3) ���̎q / 4) �� \n","�p��ɒ���\n","�����ɓ������u�Ԓ����������Ă��܂����B \n�ƂĂ��Â��ȁB\n�Ȃɂ��Â炢���ŐԂ��݂��C����B\n���܂肱���ɂ͂������Ȃ��ȁB","1",0,1,17,

	"����������","��������܂���B","1991","","4",0,0,18,


	//"�a��","��������܂���B","1991","���b�Z�[�W�Ȃ�","4",0,0,0,

	//"�a��","1+3=6  1+4=5\n4+2=4  3+5=2\n     2+5=?","1991","���b�Z�[�W�Ȃ�","3",0,1,1,
	//"�K�i","��������܂���B","1991","���b�Z�[�W�Ȃ�","4",0,0,2,

	//	"�䏊","���̒��Ɉ�����ԈႢ������\n���̖�Ⴂ�Ƃ͉��ł��傤���H\n1  2  3  4  5\n  6  7  8  9\n  10  11  12\n","1991","���b�Z�[�W�Ȃ�","4",0,1,3,

	//"����","�悱������͐��E�ꓪ�̗ǂ��j�q���Z���ł�\n���̂悱������ł����i�ł��Ȃ�������w�͂ǂ��ł��傤��","1991","���b�Z�[�W�Ȃ�","4",0,1,4,

	//"�g�C��","?�ɂ͉�������ł���\n�u����v�́u�X�q�v�@�u������v�́u�y���v\n�u�m��v�́u���v�u����v�́u����v\n�u�ޏ��v�́u??�v","1991","���b�Z�[�W�Ȃ�","4",0,1,5,

	//"�n��","1+1=?","1991","���b�Z�[�W�Ȃ�","2",0,1,6,

	//"�L��","�Ȃɂ��Ȃ�","1991","���b�Z�[�W�Ȃ�","4",0,0,7,

	//"����","��������܂���B","1991","���b�Z�[�W�Ȃ�","4",0,0,8,

	//"����","��������܂���B","1991","���b�Z�[�W�Ȃ�","4",0,0,9,

	//"����","?�ɓ��鐔���́H\n1+1=3\n1+0=2\n1-1=2\n11+11=5\n11+12=4\n111+1111=?\n","5+5","���b�Z�[�W�Ȃ�","10",0,1,10,

	//"�K�i","��������܂���B","1991","���b�Z�[�W�Ȃ�","4",0,0,11,

	//"�Q��","������4�ł��B","1991","���b�Z�[�W�Ȃ�","4",0,0,12,

	//"����13","������4�ł��B","1991","���b�Z�[�W�Ȃ�","4",0,1,13,

	//"����14","������4�ł��B","1991","���b�Z�[�W�Ȃ�","4",0,0,14,

	//"����15","��������܂���B","1991","���b�Z�[�W�Ȃ�","4",0,0,15,

	//"����16","���𔭌����܂����B","1991","���b�Z�[�W�Ȃ�","4",1,0,16,

	//"����17","�����`�͂Ȃ񂱂����ł��傤�H\ne9eeeeeeeEe#eeeeee#e#eeeeeee9e9eeeeee9e\ne         e        e         e        e\ne         e        e         e        e\ne         e   DeEeXeXGG9e    e        e\ne         e   W    e    #    e        e\ne yyyyyyW e W,9yKW e yy e yy e yyyyyy e\ne WWWWWWK e W,95uW e WW e WW e WWWWWW e\ne         e   W    e    9    e        e\ne         e   De9Eye5EE#e    e        e\ne         e        e         e        e\ne         e        e         e        e\neDeeeeeeGzeXeeeeeeXeDeeeeeeezeDeeeeeeze\ne         e        e         e        e\ne         e        e         e        e\ne         e   WG##WeW#9zE  , e        e\ne         e   X    e    e    e        e\ne         e   u    e    9    e        e\nezeeeeeeezeDeEeeGeDeXeGDeDGGXeyGGGGGGDe\ne         e   K    e    #    e        #\ne         e   D    e    e    e        G\ne         e   ,GGeXeyEE9X    e        E\ne         e        e         e        9\ne uKKKKKu e KKKKKK e WWWWWWW e yyyyyWue\nuy5555555KWK555555WKKyy5y5yyuuuyyyy55yy","1991","���b�Z�[�W�Ȃ�","40",0,1,17,



};

struct room stage1_reset[2000] = {	//�����̓f�[�^�\���̃��Z�b�g





	"�a��","��������܂���B","1991","���b�Z�[�W�Ȃ�","4",0,0,0,

	/**/	"�a��","1+1=3, 1+0=2 ,1-1=2, 11+11=5, 11+12=4, 111+1111=? \n?�ɂȂɂ��͂���ł��傤�B\n �I��: 1) 2 / 2) 1 / 3) 8 / 4) �m���\n","1�̂�","�􂪔���ɕ~����Ă��镔�����B �ƂĂ��S�n�悢�ꏊ���A���c�ꂿ���̉Ƃ��Ċ������B ","3",0,1,1,

	"�K�i","��������܂���B\n","1991","���̊K�i��2�K�Ɍq�����Ă���悤���B ","4",0,0,2,

	"�L�b�`��","��������܂���B\n","1991","�R������5������B����ȂɕK�v���낤���B �������ڂ̌������ɂ�ł��āA�K�X�R�ꂵ����������~�߂Ƃ����B","��",0,0,3,

	//"���r���O","�O�{�̐��𑫂����Ƃ��ő�Ő����`�̖ʂ̐��͂������B\n            ����������          \n         ������    ������        \n      ������          ������     \n    ������               ������  \n       ��                  ��  \n       ��                  ��  \n       ��                  ��  \n       ��                  ��  \n       ��                  ��  \n       ��                  ��  \n    ����                ������  \n      ������          ������     \n         ������    ��������       \n            ����������          \n","�T�C�R��","�ƂĂ��L���A�V�����f���A��傫�ȓV��������B �ƂĂ��f�G���B\n�傫�ȓV���̌`��0�̂悤�Ȍ`�����Ă��āA����Y��Ɍ������B\n�n���Ō�̎��͂��̋�����������ȁB\n�O�𒭂߂Ă����牽���v�������������B","���q��w",0,1,4,
	/**/	"���r���O","�Z�p�`�ɎO�{�̐��𑫂����Ƃ��ő�Ő����`�̖ʂ̐��͂������B�����݂̂œ�����\n            eeeee          \n         eee    eee        \n      eee          eee     \n    ee,               ee,  \n    e                  e5  \n    e                  e5  \n    e                  e5  \n    e                  e5  \n    e                  e5  \n    e                  e5  \n    ee                #eu  \n      eee          9ee     \n         eee    zeeu       \n            eeeey          \n�I��: 1) 4 / 2) 6 / 3) 9 / 4) 7\n","�T�C�R��","�ƂĂ��L���A�V�����f���A��傫�ȓV��������B �ƂĂ��f�G���B\n�傫�ȓV���̌`��0�̂悤�Ȍ`�����Ă��āA����Y��Ɍ������B\n�n���Ō�̎��͂��̋�����������ȁB\n�O�𒭂߂Ă����牽���v�������������B","2",0,1,4,

	"�g�C��","��������܂���B","1991","�^�C������ŏo���Ă���g�C���ł͂Ȃ����ʂ̗m���g�C���������B�J�����_�[���\���Ă���A3���ɐԊۂ������Ă������B3���̃����ɂ�5�̉E�Ə�����Ă���","��",0,0,5,

	/**/	"����","�uEOE?EXN�v ? �ɓ�����̂͂Ȃ�ł��傤�B\n�I��: 1) K / 2) X / 3) N / 4) R \n","�������p��ɂȂ��Ă���(�������łȂ�)","�ƂĂ��傫�ȗ������B \n���j�^�[�����Ă��āA�e���r�����Ȃ��炨���ɐZ���ꂻ���B\n���j�^�[�ɂ̓��[�}����SHIORI�Ə����Ă���B\n�l�̖��O���낤���B\n�l����Ɠ��Ɍ��ɂ��͂������B","4",0,1,6,

	"�L��","��������܂���B","1991","���@�Ȃ̂��A�ƂĂ��L���L����","4",0,0,7,

	"����","�^���X���J�����献���݂��������̌��炵���B","1991","�^���X���u���Ă���A���������肻�����B ","4",1,0,8,

	/**/	"���ʑ�","�����`�͉������ł��傤���H\neeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\ne         e        e         e        e\ne         e        e         e        e\ne         e   eeeeeeeeeee    e        e\ne         e   W    e    #    e        e\ne         e   W    e    #    e        e\neeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeze\ne         e   e    e    e    e        e\ne         e   W    e    #    e        e\ne         e   eeeeeeeeeee    e        e\ne         e        e         e        e\ne         e        e         e        e\neeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeze\ne         e        e         e        e\ne         e        e         e        e\ne         e   eeeeeeeeeee    e        e\ne         e   e    e    e    e        e\ne         e   e    e    e    e        e\neeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\ne         e   e    e    e    e        e\ne         e   e    e    e    e        e\ne         e   eeeeeeeeeee    e        e\ne         e        e         e        e\ne         e        e         e        e\neeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee \n�I��: 1) 30 / 2) 40 / 3) 35 / 4) 36 \n","2�~2, 3�~3, 4�~4","���u���V����u���Ă������B������ȊO�Z��ł��Ȃ��̂��낤�B���ɉf�肱�ރ{�N�����Ă���Ɖ����v���o�������ȋC������B ","2",0,1,9,

	/**/	"����","���̒��Ɉ�����ԈႢ������\n���̖�Ⴂ�Ƃ͉��ł��傤��\n1  2  3  4  5\n  6  7  8  9\n  10  11  12\n(�ꕶ���œ����Ȃ����j\n","�����͊֌W�Ȃ�","�C��2������B \n�j���Ə����ŁA�{�N�̌C�Ƃ�����̌C���낤���B\n������͏o�������͂������ǁA�Ȃ�ł���񂾂낤�H\n�����v���o���������B ","��",0,1,10,

	"�K�i","��������܂���B","1991","���̊K�i��1�K�Ɍq�����Ă���悤���B","4",0,0,11,

	"�L��","��������܂���B","1991","���낢��ȊG�������Ă���B \n�L���ȉ�Ƃ��`�������̂ł��낤���B\n�ƂĂ����������B\n��ԍ��ɂ́u3�v�Ə����ꂽ�����̃f�b�T�������邪�A\n����͈��������B","4",0,0,12,

	/**/	"�Q��","�݂񂬂���͐��E�ꓪ�̗ǂ��j�q���Z���ł��B���݂̂񂬂���ł����i�ł��Ȃ�������w�͂ǂ��ł��傤�B\n�I��: 1) ���q��w / 2) ������w / 3) �����H�ȑ�w / 4) �@����w \n","�j���ʂ��Ȃ�","�ǂ����Ō����������Ƃ̂���w�A�s�����݂����B \n���F�̉Ԃ����Ă��āA�ƂĂ����킢�炵���B������̕i�����낤�B\n��������Ƃ����肪�w�A�s�������Ă���̂�z���ł����B\n�厖�Ȃ��̂Ȃ̂��ȁc�B\n���Ɍ��ɂ��͂������B\n�����v���o�������ȋC������","1",0,1,13,

	/**/	"����2","1+3=6  1+4=5  4+2=4  3+5=2  2+5=? ?�ɂ͂���̂͂Ȃ�ł��傤�B\n �I�� 1) 3 / 2) 2 / 3) 1 / 4) 9 \n","10","�����ɂ͈�x\n�K�ꂽ�C������B","1",0,1,14,

	"����3","��������܂���","1991","���b�Z�[�W�Ȃ�","6",0,0,15,

	"�͂���","0","1991","","0",0,0,16,

	/**/ "�q��","�u����v�́u�X�q�v,�u������v�́u�y���v,�u�m��v�́u���v,�u����v�́u����v,�u�ޏ��v�́u�H�v \n? �ɂ͂�����̂͂Ȃ�ł��傤�B\n �I��: 1) �� / 2) ���� / 3) ���̎q / 4) �� \n","�p��ɒ���\n","�����ɓ������u�Ԓ����������Ă��܂����B \n�ƂĂ��Â��ȁB\n�Ȃɂ��Â炢���ŐԂ��݂��C����B\n���܂肱���ɂ͂������Ȃ��ȁB","1",0,1,17,

	"����������","��������܂���B","1991","","4",0,0,18,



};

struct hero katakura[50] = {	//��l���̓f�[�^�\����

	0,0
};

struct hero katakura_reset[50] = {	//��l���̓f�[�^�\����

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
		printf("����\n");
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
	//�@map�̏�����,�L���̃p�[�c�̏�����
	//�Q�[�����n�܂�ƃ}�b�v�i���~�j�̍\���̂����������ē�i���j�A�A�C�e���A���b�Z�[�W�Ȃǂ̔z�u������������B
	//�@�L���̃p�[�c�̏�����
	//�L���̃p�[�c�̐�������������肪����e�����ɂP�������Ė߂����ߏ���������B
	//�@�N�C�Y�̏�����
	//������������������ƋL���̃p�[�c���Q�b�g�ł���悤�ɏ���������B
	//�@�A�C�e���̏�����
	//�A�C�e���i���A���b�Z�[�W�j�����̈ʒu�ɖ߂����ߏ���������B
	memcpy(&katakura, &katakura_reset, sizeof(katakura_reset));
	//��l���̏�����
	//�Q�[�����n�܂�Ǝ�l���͌��߂��ʒu�ƃC���x���g��������������B

	move = 10;
	//�@�ړ��񐔂̏�����
	//�ړ��񐔂��P�O�ɏ��������v���C�ł���悤�ɂ��邽�ߏ���������B

}

void title() {
	//�@�^�C�g���ƃ��[����\���@
	//�^�C�g���ƃ��[����\�����v���C���[�ɃQ�[���𗝉�������B
	printf("��        ��        ��   ��    ��   ������  ����������  ��������\n");
	printf(" ��      ����      ��    ��    ��     ��        ��      ��      \n");
	printf("  ��    ��  ��    ��     ��������     ��        ��      ��������\n");
	printf("   ��  ��    ��  ��      ��    ��     ��        ��      ��      \n");
	printf("    ����      ����       ��    ��     ��        ��      ��      \n");
	printf("     ��        ��        ��    ��   ������      ��      ��������\n\n");
	printf("�@�@�@��     ��     ��      ������   ������   ��������\n");
	printf("�@�@�@����   ��   ��  ��      ��    ��    ��  ��      \n");
	printf("�@�@�@�� ��  �� ��      ��    ��     ��       ��������\n");
	printf("�@�@�@��  �� �� ��      ��    ��       ����   ��      \n");
	printf("�@�@�@��   ����   ��  ��      ��    ��    ��  ��      \n");
	printf("�@�@�@��     ��     ��      ������    ������  ��������\n\n");
	printf("\n");
	printf("Press enter key.");
	c = getchar();
	system("cls");
}



void rule() {		//Prologue�̕\��
					//�Q�[���̃X�g�[���[�␢�E�ςƃQ�[���̌��݂̏󋵂��v���C���[�ɗ��������邽��Prologue��\������B
	printf("�������[���̐�������\n\n");
	printf("1.����̕���ƂȂ鉮�~�̒��ɂ́w�L���̃J�P���x��8�B����Ă���A���́w�L���̃J�P���x���h�ł�����葽���h�������邱�Ƃ��A���̃Q�[���̖ړI�ł���B\n\n");
	printf("2.�w�T���x�Ƃ����R�}���h�����݂��邪�A���̃R�}���h���������ꏊ�Ŏ��s���鎖�ɂ��A���̏ꏊ�ɂ�����w�C�x���g�x����������B�w�T���x�R�}���h�̎g�p�񐔂́w10��x�܂łȂ̂ŁA�v��I�Ɏg���ׂ��B\n\n");
	printf("3.�w�L���̃J�P���x�́w�C�x���g�x�̈�ł���w���x�𔭌����A����ɐ������鎖�Ŏ�ɓ���B\n\n");
	printf("4.�w���x�������ہw�T���x�R�}���h���g�p���鎖�ɂ��A�w�q���g�x�����邱�Ƃ��ł���B�ǂ����Ă���肪�����Ȃ����Ɋ��p���ׂ��B\n\n");
	printf("5.�w���x�͈�x�ԈႦ��Ə��ł��Ă��܂��A�Ē���͏o���Ȃ��B\n\n");
	printf("6.�w�Q���iX�j�x�w�L���iX�j�x�ƌ��������̓}�b�v���A�w(��)�x�}�[�N�̓v���C���[��\���B�Ⴆ�΁A�w�Q���i���j�x�ƂȂ��Ă���ꍇ�A�v���C���[���Q���ɋ��鎖���Ӗ�����B\n\n");
	printf("7.�Q�[�����̏d�v�A�C�e���ł���w���x����肵���ꍇ�A����ȍ~�v���C���[�������A�C�R���́w���x����w���x�ɕω�����B\n\n");
	printf("8.�Q�[���I���܂łɏW�߂��w�L���̃J�P���x�̌��ɂ��A�G���f�B���O���ω�����B���Ԃɗ]�T������΁A���ЍĒ��킵�āA���ǂ��G���f�B���O��ڎw�����B\n\n");

	/*printf("�������[���̐�������\n\n");
	printf("10�̑�؂Ȏ�\n");
	printf("1.���MAP���\������A���̓v���C���[�̈ʒu��\���B\n");
	printf("2.�T���񐔂���������A[�T��]�̃R�}���h��I������ƕK�R�I�ɒT���񐔂�����B\n");
	printf("3.�T���񐔂�12��Ƃ���B\n");
	printf("4.�Z���\������Ă��āA�A�C�e���ł��錮����肷��Ɓ��ւƕω�����B\n");
	printf("5.�L���̌��Ђ��ő��8���肵�Ȃ���΂Ȃ�Ȃ��B\n");
	printf("6.�L���̌��Ђ͂������̏ꏊ��T�����ɖ�肪����A�������Ƃ��ł��������Ƃ���B�@�܂��A�q���g���g�p����ꍇ�A[�T��]�������Ƃ݂Ȃ���A�T���񐔂�����B\n");
	printf("7.���̉𓚂��ԈႦ��ƈ�O�̕����ɂ��ǂ�B���͉��������邪�T�����Ȃ���΂Ȃ�Ȃ��B\n");
	printf("8.�X�g�[���[���y���߁B\n");
	printf("9.�L���̌��Ђ̐��ɉ����āA�V�i���I�ω��B\n");
	printf("10.���x�����킵�āA���ׂẴV�i���I��T���I\n\n");*/

	printf("�����R�}���h����\n\n");
	printf("1.ENTER / ���̃y�[�W\n");
	printf("2.�ړ� / ����\n");
	printf("3.�I���@�@�@ / �^�C�s���O\n");
	printf("Enter..>>");
	c = getchar();
	system("cls");

}

void prologue() {		//Prologue�̕\��
						//�Q�[���̃X�g�[���[�␢�E�ςƃQ�[���̌��݂̏󋵂��v���C���[�ɗ��������邽��Prologue��\������B

	printf("���v�����[�O��\n\n");
	printf("�������Ă����C������B\n\n");
	printf("�ƂĂ��A�ƂĂ���؂������N���̏Ί�B���B������B�Y��ȍ������B\n\n");
	printf("���̔��Ɍ��锒���w�A�s���̓{�N���a�����ɑ��������m���B\n\n");
	printf("�ƂĂ��g�����āA���������̂Ȃ����m�������͂��Ȃ̂ɁA\n\n");
	printf("�����̓{�N�̑̂�ʂ蔲���A�ǂ��������֍s���Ă��܂��C�����āA\n\n");
	printf("�Ђǂ��s���ȋC�����ɂȂ�c\n\n");
	printf("Enter..>>");
	c = getchar();
	system("cls");
}

/*void pig() {
//printf("���O�͂R�����ȓ��ɂ��Ă��������B\n");
printf("���O��ݒ肭�������B\n");
printf("���Ȃ��̖��O�́H\n");
printf("���O�F");
scanf("%s", &name);
system("cls");

}*/

void story1() {
	printf("������u�c�����c��H�v\n"); c = getchar();
	printf("������u�����͈�́c�@���������ǂ����āc�@�O�b�c�I�v\n"); c = getchar();
	printf("���m��ʕ����Ŗڂ��o�߂��B\n"); c = getchar();
	printf("���܂ł̂��Ƃ��v���o�����Ƃ��邪�A������ז����邩�̂悤�ɋL���Ƀz���C�g�m�C�Y��������A���Ɍ��ɂ��������B\n"); c = getchar();
	printf("�v�킸��������悤�Ƙr�𓮂����ƁA�ӂƁA�E��ɂق�̂�ƒN���̑̉����������B\n"); c = getchar();
	printf("�̉���������ق��ɖڂ����ƁA�����ɂ̓{�N�̎���؂����Ɉ���Ȃ���A�X�[�X�[�ƐQ�������ĂĐQ�Ă��鏭���������B\n"); c = getchar();
	printf("������u���̎q�A�ǂ����Łc�v\n"); c = getchar();
	printf("�L����T�낤�Ƃ�����A��͂蓪�Ɍ��ɂ��z��B\n"); c = getchar();
	printf("�{�N���N�������ɋC�Â����̂��ڂ̑O�̏�������ыN�����B\n"); c = getchar();
	printf("�H�H�H�u�悩�����c�c�I�@�ڂ��o�߂��̂ˁI�H�v\n"); c = getchar();
	printf("�����͈��g�Ɗ���̓��荬���������������B\n"); c = getchar();
	printf("�H�H�H�u���������S�z�����񂾂�I�H�@�˂�������ƁI�@�����ǂꂾ���S�z�������킩���Ă�I�H �v\n"); c = getchar();
	printf("�{�N�̂��Ƃ�S�z���Ă���Ă����炵�������́A�󋵂������炸�Ƀ{�P�b�Ƃ��Ă���{�N�̕\������āA�j��c��܂��Ă���B\n"); c = getchar();
	printf("������u�c�c�����ƃS�����A�L�~�͒N�H�v\n"); c = getchar();
	printf("�H�H�H�u���c�c�H�v\n"); c = getchar();
	printf("�����͋����̐���������B\n"); c = getchar();
	printf("�H�H�H�u�킽���̂��Ɓc�c�o���ĂȂ��́c�c�H�v\n"); c = getchar();
	printf("�ޏ��͂����������A�v���o���Ȃ����͎̂v���o���Ȃ��B\n"); c = getchar();
	printf("������u���߂�A�{���ɉ����v���o���Ȃ��񂾁c�v\n"); c = getchar();
	printf("������u�������A�L�~�̂��Ƃ��c�v\n"); c = getchar();
	printf("������u���A���́A�悯��Ζ��O�������Ă��������ȁc�H�v\n"); c = getchar();
	printf("������u���A����B���̖��O�͂�����B�c�c�ꉞ�A�L�~�́w�ޏ��x�Ȃ񂾂�H�v\n"); c = getchar();
	printf("�����̖��O�́w�A�J���x�ƌ����炵���B\n"); c = getchar();
	printf("������u�����肳��A�S�z�����ăS�����v\n"); c = getchar();
	printf("������u�ŕa�܂ł��Ă�������݂����Ȃ̂ɁA�L�~�̂��Ƃ�Y��Ă��܂��Ȃ�āc�c�v\n"); c = getchar();
	printf("������u�c�c����ƁA���肪�Ƃ��v\n"); c = getchar();
	printf("������u���ւցc�c�B�͂��A�ǂ��������܂��āI�v\n"); c = getchar();
	printf("������u�����ƁA������������������񂾂��ǁA�����͂ǂ��H�v\n"); c = getchar();
	printf("������u�����H �����͎��ƃL�~�̂��Ƃ���H �����������A�S���Y�ꂿ����Ă�񂾂�ˁB�v\n"); c = getchar();
	printf("������u���[��A�܂��܂��F�X�ƕ����������Ƃ͂���Ǝv���񂾂��ǁc�c�v\n"); c = getchar();
	printf("�ޏ��͂��������Ȃ��痧���オ�����B\n"); c = getchar();
	printf("������u�S�����I ���A������Ɨp�������邩�炨�o�������Ȃ��Ƃ����Ȃ��񂾂�ˁv\n"); c = getchar();
	printf("������u���A�o������́c�c�H�v\n"); c = getchar();
	printf("�����ȂƂ���A�܂���l�ɂȂ�̂͏����s���������̂����A�����Ɗŕa���Ă��ꂽ�ޏ����킴�킴�o������قǂȂ̂��A�����Ƒ�؂ȗp���Ȃ̂��낤�B\n"); c = getchar();
	printf("������u����A�킩�����B�����Ă�����Ⴂ�v\n"); c = getchar();
	printf("������u����I�@�s���Ă��܁[���I�v\n"); c = getchar();
	printf("������̓o�^�o�^�Ǝx�x������ƁA�s�������ȃ{�N�����S������悤�ɁA��x������ɏ΂������Ă���o�����Ă������B\n"); c = getchar();
	printf("������u���[��B���������N�����̂ɉ������Ȃ����Ă̂͏����ދ����ȁc�v\n"); c = getchar();
	printf("������u�������B�����Ƃ̒���T�����Ă݂悤�B�����v���o�����������������邩���m��Ȃ��v\n"); c = getchar();
	printf("�{�N�̓x�b�h����N���オ��A��x�L�т�����ƁA�Ƃ̒T�����n�߂邱�Ƃɂ����B\n"); c = getchar();
	printf("NEXT>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n"); c = getchar();
	system("cls");
}



void map1_dis() {

	char map[20];
	int map_num;
	for (map_num = 0; map_num < 20; map_num++) {		 //���ݒn��'.'�ł���킷�B
		if (stage1[i].room_num == map_num) {
			map[map_num] = 'O';
		}
		else if (stage1[i].room_num != map_num) {		//���ݒn�ȊO��' '�ł���킷�B
			map[map_num] = 'X';
		}
	}
	printf("            M          A            P\n");
	printf("1F\n");
	printf("                               [ �a�� (%c) ]        \n", map[1]);
	printf("[ �K�i (%c) ][ �L�b�`�� (%c)  ][     ���r (%c)     ][ �g�C�� (%c) ][�@�� (%c) ]\n", map[2], map[3], map[4], map[5], map[6]);
	printf("[ �L�� (%c) ][    ����  (%c)  ][     �@���O       ][ ���ʑ� (%c) ][  ��     ]\n", map[7], map[8], map[9]);
	printf("[ ���� (%c) ]\n", map[10]);
	printf("------------------------------------------------------------------------------\n");
	printf("2F\n");
	printf("      [�K�i (%c) ]\n", map[11]);
	printf("[               �L�� (%c)         ][  �Q(%c) ]\n", map[12], map[13]);
	printf("[      ����2 (%c)   ][ ����3 (%c)  ][  ��    ]\n", map[14], map[15]);
	printf("[      �͂���(%c)   ][ �q�� (%c)  ]                              [????(%c)]\n", map[16], map[17], map[18]);
	printf("-----------------------------------------------------------------------------\n");
}

void messege1() {
	//�@���b�Z�[�W�̕\��
	//��l������Ԏn�߂Ă��炤�A�C�e���ł����荡��Ȃɂ����ׂ������킩��悤�b��\������B

	printf("�����b�Z�[�W��\n%s\n", stage1[i].messege);
	c = getchar();

}



void state() {
	//���݂̈ʒu���Ԃ̕\��
	//���݂̈ʒu�Ǝ����Ă�A�C�e���A�I���\��Command��\������B
	printf("      ----------------------\n");
	printf("     l ���݈ʒu�F%s       l\n", stage1[i].room_name);

	if (katakura[0].inventory_num == 0) {
		printf("     l ���F��               l\n");
	}
	else if (katakura[0].inventory_num == 1) {
		printf("     l ���F��               l\n");
	}
	printf("     l �L���̃p�[�c�F%d      l\n", katakura[0].remember);

	printf("     l �T���񐔁F%d         l\n", move);
	printf("      ----------------------", move);
	printf("\n");



}


void slove() {
	//�����
	//�v���C���[�̉�ʂɖ�肪���ꓚ����I�������������B

	strcpy_s(ans1, sizeof("0"), "0");

	/*printf("%s", &ans1);*/

	hint1 = 0;

	int j;
	/*printf("%d\n", stage1[i].part);*/
	if (stage1[i].part == 1) {

		printf(">>���<<\n%s\n", stage1[i].question);

		printf("�q���g�����܂����H\n");
		printf("1.�݂�@2.�݂Ȃ�\n");
		while (!(hint1 == 1 || hint1 == 2)) {
			hint1 = 0;
			printf("�I���F");
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
			printf("��������͂��Ă��������B\n");
			printf("�����F");
			scanf_s("%s", &ans1, sizeof(ans1));
			//printf("%d\n", ans1);
			//printf("%d\n", stage1[i].ans);


			if (!strcmp(ans1, stage1[i].ans)) {
				printf("\n");
				printf("�����ł��B\n");
				//�L���̃p�[�c����ɓ����@
				//��̖��������ċL���̃p�[�c���擾���A�A�C�e���\���̂���
				//�f�[�^���v���C���[�L�����N�^�[�i��l���j�̃f�[�^�Ɉړ�������B
				//	if (stage1[i].part == 1) {
				stage1[i].part = 0;

				

				katakura[0].remember++;
				/*printf("%d\n", stage1[i].part);*/
				printf("�L���̃p�[�c���E�����B\n\n");
				//}else if (stage1[i].part == 0) {
				//	printf("�L���̔j�Ђ��Ȃ��B\n");
				//}
				
				strcpy_s(stage1[i].question, sizeof("0"), "0");
				
				move_select();

			}

			else {
				printf("[%s]�͕s�����ł��B\n", &ans1, sizeof(ans1));
				printf("��NEXT��\n");
				
				c = getchar();
				strcpy_s(stage1[i].question, sizeof("0"), "0");
				/*		printf("�O�̕����ɋA�����B\n");
				i = p_i;  */


			}

		}


	}
	else if (stage1[i].item == 1) {
		printf("%s\n", stage1[i].question);


		//if (stage1[i].item == 1) {
		stage1[i].item = 0;
		katakura[0].inventory_num++;
		printf("�����E�����B\n");
		//}
		//else if (stage1[i].part == 0) {
		//	printf("�L���̔j�Ђ��Ȃ��B\n");
		//}
		strcpy_s(stage1[i].question, sizeof("0"), "0");
		move_select();

	}
	/*else if(stage1[i].item == 0){
				move_select1 = 0;
		// printf("�����Ȃ������̂ňړ�����B\n");
		printf("�ړ����܂����H\n");
		printf("1.�ړ� \n");
		printf("�I���F");
		scanf_s("%d", &move_select1);
		printf("\n");*/



	else {
		printf("%s\n", stage1[i].question);

		move_select();
	}


}

void move_select() {
	
	if (move == 1) {
		
		printf("�x���F�T���\�ȉ񐔂���c��P��ł��B\n");
		printf("�q���g�F�͂����̕��ɉ��������邩��\n\n");
		
	}

	if (katakura[0].remember == 8) {
		printf("�S�Ďv���o�����B\n");
		printf("�͂����Ɍ������Ă݂悤�B\n\n");
	}

	if (i == 18) {
		p_i = i;
		printf("�����������̂悤��\n"); c = getchar();
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
		// printf("�����Ȃ������̂ňړ�����B\n");
		printf("����������������������������������������������������������������������������������\n");
		printf("�ړ����܂����H\n");
		printf("1.�ړ� \n");
		printf("�I���F");
		scanf_s("%d", &move_select1);
		printf("\n");

		if (move_select1 == 1) {
			p_i = i;

			if (i == 1) {
			
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.���r���O\n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 4;
				}
				else {
					printf("��������Ȃ��B\n");
				}
			}

			//11111111111111111111111111111111111111111111111

			else if (i == 2) {
				p_i = i;
			
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.�Q�K�ɏオ�� // 2.�L��\n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 11;
				}
				else if (dir_select == 2) {

					i = 7;
				}
				else {
					printf("��������Ȃ��B\n");
				}
			}

			//22222222222222222222222222222222222222222

			else if (i == 3) {
				p_i = i;
				
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.���r���O\n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 4;
				}

				else {
					printf("��������Ȃ��B\n");
				}
			}

			//3333333333333333333333333333333333333333333

			else if (i == 4) {
				p_i = i;
			
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.�L�b�`�� // 2.���� // 3.�g�C�� // 4.���ʑ� // 5.�a��\n");
				printf("�I���F");
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
					printf("��������Ȃ��B\n");
				}
			}

			//444444444444444444444444444444444444444444444444444

			else if (i == 5) {
				p_i = i;
				
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.���r���O \n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 4;
				}

				else {
					printf("��������Ȃ��B\n");
				}

			}
			//555555555555555555555555555555555555555555555555555555555555

			else if (i == 6) {
				p_i = i;
				
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.���ʑ� \n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 9;
				}

				else {
					printf("��������Ȃ��B\n");
				}
			}
			//666666666666666666666666666666666666666666666666666666666666666666
			else if (i == 7) {
				p_i = i;
			
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.�K�i�ɏオ�� // 2.���� // 3.����\n");
				printf("�I���F");
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
					printf("��������Ȃ��B\n");
				}
			}
			//777777777777777777777777777777777777777777777777777777777777777
			else if (i == 8) {
				p_i = i;
			
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.�L�� // 2.���r���O\n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 7;
				}
				else if (dir_select == 2) {

					i = 4;
				}

				else {
					printf("��������Ȃ��B\n");
				}
			}
			//888888888888888888888888888888888888888888888888888

			else if (i == 9) {
				p_i = i;
			
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.���r���O // 2.���� \n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 4;
				}
				else if (dir_select == 2) {

					i = 6;
				}

				else {
					printf("��������Ȃ��B\n");
				}
			}
			//9999999999999999999999999999999999999999999999999999999999
			else if (i == 10) {

				p_i = i;
				
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.�L��\n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 7;
				}
				else {
					printf("��������Ȃ��B\n");
				}
			}
			//101010101110101010110101010110101010110101010
			else if (i == 11) {
				p_i = i;
			
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.��K�ɍ~��� // 2.�L��\n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 7;
				}
				else if (dir_select == 2) {

					i = 12;
				}

				else {
					printf("��������Ȃ��B\n");
				}
			}
			//111111111111111111111111111111111111111111111111111111111

			else if (i == 12) {
				p_i = i;
			
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.�K�i���~��� // 2.����2 // 3.����3 // 4.�Q��\n");
				printf("�I���F");
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
					printf("��������Ȃ��B\n");
				}
			}

			//12121212121212121212121212121212121212121212121

			else if (i == 13) {
				p_i = i;
		
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.�L�� \n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 12;
				}

				else {
					printf("��������Ȃ��B\n");
				}
			}
			//13131331313131313131313131313131313131313131313131313

			else if (i == 14) {
				p_i = i;
			
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.�L�� // 2.�͂���\n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 12;
				}

				else if (dir_select == 2) {



					printf("�����܂��Ă���B\n");
					if (katakura[0].inventory_num == 1) {
						printf("���������Ă��܂��B\n");
						printf("�����J���܂��B\n");


						i = 16;
					}


					//3
					else if (katakura[0].inventory_num == 0) {
						printf("���������Ă��Ȃ��B\n");
						printf("�����J���܂���B\n");
						i = 14;
					}



				}
			}
			//14141414141414141414141414141414141414141414141414141414141414141414

			/*else if (i == 15) {
			p_i = i;
			printf("����15\n");
			printf("�ǂ��Ɉړ����܂����H\n");
			printf("1.���L���� // 2.������17��\n");
			scanf_s("%d", &dir_select);
			if (dir_select == 1) {

			i = 12;
			}
			else if (dir_select == 2) {



			i = 17;


			}

			else {
			printf("��������Ȃ��B\n");
			}
			}
			*/
			//151515151515151515151515151515151515151515151515151515

			else if (i == 15) {
				p_i = i;
			
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.�L�� // 2.�q��\n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 12;
				}
				else if (dir_select == 2) {
					printf("\n");
					printf("�Ïؔԍ����킩��Ȃ��Ƒq�ɂւ͂����Ȃ��炵���B\n");
					printf("�ԍ����́F");
					scanf_s("%d", &pass);
					if (pass == 3530) {
						//if (pass == 3530 && katakura[0].inventory_num == 1) {

						printf("�h�A���J�����B\n");
						i = 17;
					}
					else {

						printf("�Ïؔԍ����Ԉ�����悤���B");
						i = 15;

					}

				}
			}

			else if (i == 16) {
				p_i = i;
		
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.����2�@// 2.????\n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 14;
				}
				else if (dir_select == 2) {

					i = 18;
				}
				else {
					printf("��������Ȃ��B\n");
				}
			}

			//171717171717171717171717171717171717171717

			else if (i == 17) {
				p_i = i;
			
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.����3 \n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 15;
				}

				else {
					printf("��������Ȃ��B\n");
				}
			}

			c = getchar();

		}

	}
	else {
		move_select1 = 0;
		printf("����������������������������������������������������������������������������������\n");
		printf("�ړ����܂����H\n");
		printf("1.�ړ� 2.�T��\n");
		printf("�I���F");
		scanf_s("%d", &move_select1);
		printf("\n");

		if (move_select1 == 1) {
			p_i = i;

			if (i == 1) {
		
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.���r���O\n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 4;
				}
				else {
					printf("��������Ȃ��B\n");
				}
			}

			//11111111111111111111111111111111111111111111111

			else if (i == 2) {
				p_i = i;
			
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.�Q�K�ɏオ�� // 2.�L��\n");
				printf("�I���F");
				scanf_s("%d", &dir_select);

				if (dir_select == 1) {

					i = 11;
				}
				else if (dir_select == 2) {

					i = 7;
				}
				else {
					printf("��������Ȃ��B\n");
				}
			}

			//22222222222222222222222222222222222222222

			else if (i == 3) {
				p_i = i;
			
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.���r���O\n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 4;
				}

				else {
					printf("��������Ȃ��B\n");
				}
			}

			//3333333333333333333333333333333333333333333

			else if (i == 4) {
				p_i = i;
				
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.�L�b�`�� // 2.���� // 3.�g�C�� // 4.���ʑ� // 5.�a��\n");
				printf("�I���F");
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
					printf("��������Ȃ��B\n");
				}
			}

			//444444444444444444444444444444444444444444444444444

			else if (i == 5) {
				p_i = i;
				
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.���r���O \n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 4;
				}

				else {
					printf("��������Ȃ��B\n");
				}

			}
			//555555555555555555555555555555555555555555555555555555555555

			else if (i == 6) {
				p_i = i;
			
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.���ʑ� \n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 9;
				}

				else {
					printf("��������Ȃ��B\n");
				}
			}
			//666666666666666666666666666666666666666666666666666666666666666666
			else if (i == 7) {
				p_i = i;
			
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.�K�i���オ�� // 2.���� // 3.����\n");
				printf("�I���F");
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
					printf("��������Ȃ��B\n");
				}
			}
			//777777777777777777777777777777777777777777777777777777777777777
			else if (i == 8) {
				p_i = i;
				
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.�L�� // 2.���r���O\n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 7;
				}
				else if (dir_select == 2) {

					i = 4;
				}

				else {
					printf("��������Ȃ��B\n");
				}
			}
			//888888888888888888888888888888888888888888888888888

			else if (i == 9) {
				p_i = i;
			
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.���r���O // 2.���� \n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 4;
				}
				else if (dir_select == 2) {

					i = 6;
				}

				else {
					printf("��������Ȃ��B\n");
				}
			}
			//9999999999999999999999999999999999999999999999999999999999
			else if (i == 10) {
			
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.�L��\n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 7;
				}
				else {
					printf("��������Ȃ��B\n");
				}
			}
			//101010101110101010110101010110101010110101010
			else if (i == 11) {
				p_i = i;
			
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.��K�ɍ~��� // 2.�L��\n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 7;
				}
				else if (dir_select == 2) {

					i = 12;
				}

				else {
					printf("��������Ȃ��B\n");
				}
			}
			//111111111111111111111111111111111111111111111111111111111

			else if (i == 12) {
				p_i = i;
			
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.�K�i���~��� // 2.����2 // 3.����3 // 4.�Q��\n");
				printf("�I���F");
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
					printf("��������Ȃ��B\n");
				}
			}

			//12121212121212121212121212121212121212121212121

			else if (i == 13) {
				p_i = i;
			
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.�L�� \n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 12;
				}

				else {
					printf("��������Ȃ��B\n");
				}
			}
			//13131331313131313131313131313131313131313131313131313

			else if (i == 14) {
				p_i = i;
			
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.�L�� // 2.�͂���\n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 12;
				}

				else if (dir_select == 2) {



					printf("�����܂��Ă���B\n");
					if (katakura[0].inventory_num == 1) {
						printf("���������Ă��܂��B\n");
						printf("�����J���܂��B\n");


						i = 16;
						
					}


					//3
					else if (katakura[0].inventory_num == 0) {
						printf("���������Ă��Ȃ��B\n");
						printf("�����J���܂���B\n");
						i = 14;
					}



				}
			}
			//14141414141414141414141414141414141414141414141414141414141414141414

			/*else if (i == 15) {
			p_i = i;
			printf("����15\n");
			printf("�ǂ��Ɉړ����܂����H\n");
			printf("1.���L���� // 2.������17��\n");
			scanf_s("%d", &dir_select);
			if (dir_select == 1) {

			i = 12;
			}
			else if (dir_select == 2) {



			i = 17;


			}

			else {
			printf("��������Ȃ��B\n");
			}
			}
			*/
			//151515151515151515151515151515151515151515151515151515

			else if (i == 15) {
				p_i = i;
		
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.�L�� // 2.�q��\n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 12;
				}
				else if (dir_select == 2) {
					printf("�Ïؔԍ����킩��Ȃ��Ƒq�ɂւ͂����Ȃ��炵���B\n");
					printf("�ԍ����́F");
					scanf_s("%d", &pass);
					if (pass == 3530) {
						//if (pass == 3530 && katakura[0].inventory_num == 1) {

						printf("�h�A���J�����B\n");
						i = 17;
					}
					else {

						printf("�Ïؔԍ����Ԉ�����悤���B");
						i = 15;

					}

				}
			}

			else if (i == 16) {
				p_i = i;
	
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.����2�@// 2.????\n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 14;
				}
				else if (dir_select == 2) {

					i = 18;
				}
				else {
					printf("��������Ȃ��B\n");
				}
			}

			//171717171717171717171717171717171717171717

			else if (i == 17) {
				p_i = i;
				
				printf("�ǂ��Ɉړ����܂����H\n");
				printf("1.����3 \n");
				printf("�I���F");
				scanf_s("%d", &dir_select);
				if (dir_select == 1) {

					i = 15;
				}

				else {
					printf("��������Ȃ��B\n");
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
	printf("���̕����͈ٗl�ɐÂ��ŁA�ǂ��ƂȂ��s�C���ȕ��͋C��Y�킹�Ă����B\n"); c = getchar();
	printf("���邢�Q���Ɋ���Ă����{�N�̖ڂɂ́A���̔��Â������̒��̓V���G�b�g���炢�ɂ��������Ȃ������B\n"); c = getchar();
	printf("�ڂ��Â炷�ƍ����l�e�̂悤�Ȃ��̂��������B\n"); c = getchar();
	printf("�{�N�͕ǂɎ��T��悤�ɂ��āA�����������̓d�C�̃X�C�b�`��T�����B\n"); c = getchar();
	printf("�d�C��t����ƁA�����ɂ͏������֎q�ɔ���Ă����B\n"); c = getchar();
	printf("�{�N�͔��˓I�ɏ����Ȃ���΂Ȃ�Ȃ��Փ��ɋ��ꂽ�B\n"); c = getchar();
	printf("�����͋C�������Ă���̂��|���悤�ɂ��č����Ă���B\n"); c = getchar();
	printf("�g�̂�h����N�������Ƃ���ƁA\n"); c = getchar();
	printf("������u��仁A��仁A��仁I�I�v\n"); c = getchar();
	printf("�{�N�͂Ȃ����܂𗬂��Ȃ�u��仁v�Ɖ��x���Ăт����N�������Ƃ��Ă����B\n"); c = getchar();
	printf("�Ȃ�ŋ����Ă���̂��킩��Ȃ��B\n"); c = getchar();
	printf("�n�߂Ă������͂��̐l�Ȃ̂ɁB\n"); c = getchar();
	printf("������ߕt����悤�ɋꂵ���B\n"); c = getchar();
	printf("�܂��~�܂�Ȃ��B\n"); c = getchar();
	printf("������u��仁A��仁A��仁I�I�I�I�I�@�N���Ă����I�I�@��仁I�I�v\n"); c = getchar();
	printf("�{�N�͕K���Ɏ�仂��ĂтȂ���g�̂��䂷���Ă����B\n"); c = getchar();
	printf("��仁u����Ȃɉ��x���Ă΂�Ȃ������ĕ������Ă��v\n"); c = getchar();
	printf("��仂͞N�O������ԂŃ{�N��S�z�����Ȃ��悤�ɐ����|���Ă��ꂽ�̂��B\n"); c = getchar();
	printf("�{�N�͐g�̂̑S���̗͂������Ă��܂����ɍ��荞��ł��܂����B\n"); c = getchar();
	printf("������u�悩�����A�悩������v\n"); c = getchar();
	printf("���ׂĖY��Ă����̂ɁA���̊Ԃɂ��L�����v���o���Ă��Ă����B\n"); c = getchar();
	printf("�������A���D�B\n"); c = getchar();
	printf("���߂�ȁB\n"); c = getchar();
	printf("�i�ߋ��j--------------------------------------------------------------------------------------------------------------\n"); c = getchar();
	printf("��仂Ƃ͍��Z�̎��̌�y�Ɛ�y�̕����̊֌W�ł������B\n"); c = getchar();
	printf("�{�N�̖��O�͋�(������)�A�e�j�X���ɏ������Ă����B\n"); c = getchar();
	printf("�e�j�X���ł͑S����ڎw���قǋ����͂Ȃ��������A����������K���s�����ł͂���������ʂɓ��܂��Ă����B\n"); c = getchar();
	printf("�{�N�͏��������납��e�j�X������Ă����̂ŁA��������������������C�����Ă����B���ł����Δ����ċ��������̂��{�N�̔ޏ���仂ł���A�����̃L���v�e����C����Ă����قǂ̎��͎ҁB���C�Ŗ��邭�A�V�^ࣖ��ł݂�Ȃ����������Ă���鑶�݂��B\n"); c = getchar();
	printf("���邷����ῂ������݂ŁA�{�N�ɂ͂��������Ȃ��B\n"); c = getchar();
	printf("��仂Ƃ͗c�t������̗c����� �̂���̕t�������A���������납��V�Ԏ���w�Z�ɍs���Ƃ��͉Ƃ��ߏ����Ƃ������R�ňꏏ�ɂ��鎖�����������B\n"); c = getchar();
	printf("�{�N�̂ǂ����D���ɂȂ��Ă��ꂽ�̂��킩��Ȃ����A���w�𑲋ƂƂƂ��ɍ���������A�Ԏ�������ɂȂ��A\n"); c = getchar();
	printf("��仁u������ˁH���ꂩ�����낵���˂��I�v\n"); c = getchar();
	printf("�Ɩ������t�����������ɂȂ������A�{�N�͂ƂĂ����ꂵ���������Ƃ��o���Ă���B\n"); c = getchar();
	printf("���ꂩ��{�N��͓������Z�ɓ���A�e�j�X���Ŋ������Ă��������A���w�N�ŕ����ƕ������ƂȂ����B\n"); c = getchar();
	printf("���w�N�ƂȂ�ƂƂ��ɐV�������e�j�X���ɓ����Ă����B���̐V�����̈�l�����D�ł������B\n"); c = getchar();
	printf("���D�͕��Â��ł��܂�b���Ȃ��̂������ŁA�����V�����Ɛe����ł�l�q�͂Ȃ��A��仂Ƃ͐����΂̐��i���B\n"); c = getchar();
	printf("�Â��ł���̂������ƂȂ�ƂƂĂ���ÂŌv�Z�����A����̃X�L��_���v���C�𓾈ӂƂ��Ă����B\n"); c = getchar();
	printf("�Ȃ��Ȃ��݂�Ȃ̗ւɓ��낤�Ƃ��Ȃ����D�������˂���仂͐��i�㖳���ł��Ȃ��A�w�H��V�тɍs���Ƃ��ɖ������U���A�΂��ĉ߂������Ԃ�������̂��B\n"); c = getchar();
	printf("����ȓ���������O�ɂȂ��Ă������A�{�N�͎��D�ɑ��k�ɏ���Ăق����ƌĂ΂ꂽ�B\n"); c = getchar();
	printf("���k�̓��e�͎������g��ς������Ƃ������e�ŁA�u�ǂ��������仂̂悤�ɂȂ�܂����H�v�Ǝ��₳��A�{�N�́u���̂܂܂ł����񂶂�Ȃ����ȁH�v�Ǝ��ɒP���ɓ������̂��B\n"); c = getchar();
	printf("���D�́u�����ł����v�ƈꌾ�����ƁA�񌾖ڂɁu�󂪑�D���ł��v�Ɠ������̂��B\n"); c = getchar();
	printf("�{�N�͈�u�A�����^�����ɂȂ��Ă��܂������A��ÂɂȂ�u���߂�ˁv�Ƃ������B\n"); c = getchar();
	printf("���D�͂��̏u�ԁu���̂܂܂ł͋�Ƃ͕t�������Ȃ��̂ł��ˁv�ƈꌾ�̂����A�����Ă������B\n"); c = getchar();
	printf("���̓����|����ƁA�����͕��Â��ł������̂��������Č��C�� �U�����Ă��鎍�D�̎p���������B\n"); c = getchar();
	printf("���̎p���݂��{�N�͂����ɋC���t���A��仂̐^�����Ƃ����Ă��邱�Ƃ��킩�����B\n"); c = getchar();
	printf("��仂͏������邭�Ȃ����̂��Ȓ��x�ŋC�Â��Ă��Ȃ��������A�{�N�͐\����Ȃ��C�Â��Ȃ��ӂ�������̂��B\n"); c = getchar();
	printf("���ꂩ����������A�{�N�����͑��Ƃ����̂��B\n"); c = getchar();
	printf("�����I�������Ń{�N�Ǝ�仂̑O�Ɏ��D�����āA\n"); c = getchar();
	printf("���D�u��ς����b�ɂȂ�܂������I�A�{���ɂ��肪�Ƃ��������܂������I�v\n"); c = getchar();
	printf("�Ɗ��ӂ̌��t���|���Ă��ꂽ�̂��B\n"); c = getchar();
	printf("���D�͂����b�ɂȂ����������Ԃ��������Ƃ������ƂŁA�Ƃɏ����ꂽ�B\n"); c = getchar();
	printf("���D�͎��Y�Ƃ̖��ŕʑ��������Ă���炵���A�ʑ��ɎO�l�ōs�����ƂɂȂ����̂��B\n"); c = getchar();
	printf("�{�N�����͕ʑ��Ɍ��������ƂɂȂ����B\n"); c = getchar();
	printf("�ʑ��͐X�̒��������i�񂾏��ɂ���A�X�Ɉ͂܂ꂽ���؂ȉƂ��Ȃ�ł����B\n"); c = getchar();
	printf("���ɓ���ƁA���ւɂ͑傫�ȃL�����o�X�������Ă���A�|�p�Ƃ̕`�����悤��\n"); c = getchar();
	printf("�N�₩�ȐF�����̉Ԃ������Ă����B\n"); c = getchar();
	printf("���D�u��y���A�C�y�ɂ������Ă����������I�v\n"); c = getchar();
	printf("�ƌ��C�Ȑ��Ń{�N����}���Ă��ꂽ�B\n"); c = getchar();
	printf("��仁u������܂��܂��A���̉Ƃɂ͂�����Z��łȂ��́H�v\n"); c = getchar();
	printf("���ւ����������{�N�����̌C�����Ȃ��A���ɂ͒N�����Ȃ��Ǝv�������A����Ȃɂ��L���ƂɃ{�N���������Ȃ̂��M�����Ȃ������B\n"); c = getchar();
	printf("��l��炵�ɂ͂��������Ȃ����炢���؂ȉƁB�������Ɏ��Y�Ƃ̖����B\n"); c = getchar();
	printf("���D�u�����ł��ˁA���̉Ƃ͎����������邽�߂����Ɍ��Ă�ꂽ�̂ŁA��������Ȃ��ł�����I�v\n"); c = getchar();
	printf("��仁u���������΂��̉Ƃŉ�������́H�v��仂̓T�v���C�Y�����Ă��炦��Ǝv�����̂��킴�Ƃ炵���`�����B\n"); c = getchar();
	printf("�{�N�����͉����m�炳��Ă��Ȃ���ԂŁA���D�ɘA��ė����Ă����̂��B\n"); c = getchar();
	printf("�킴�킴�ʑ��ɗ����񂾂���A����Ȃ��ƂȂ񂾂낤���B\n"); c = getchar();
	printf("���D�u�܂��閧�ł����I�v\n"); c = getchar();
	printf("���D�̓T�v���C�Y���������̂��A�ǂ����S���E�L�E�L�����Ă���C������Y�킹�Ă����B\n"); c = getchar();
	printf("���D�u������2�K�ɍs���܂��A2�K���牮���������Ɍq�����Ă��āA�ĊO�����̒����L����ł�����I�v\n"); c = getchar();
	printf("��仁u�����˂��I�A�͂₭�������[�I�v\n"); c = getchar();
	printf("��仂͎q���݂����ɂ͂��Ⴂ�ł���B\n"); c = getchar();
	printf("�{�N�������͉����������Ȃ�ăA�j���݂����ŁA��������������B\n"); c = getchar();
	printf("���~�̕����ɂ͂��낢��ȃC���e���A�������Ă��āA���ƂĂ����������B\n"); c = getchar();
	printf("�{�N���1�K����2�K�ɂ��������B�����������Ɍq����K�i�́A�ʂ̂Ƃ���ɂ���炵���B\n"); c = getchar();
	printf("���D�u�������ł����I�v\n"); c = getchar();
	printf("�{�N��͎��D�̌����܂܂ɒʘH������A�Q���炵�������ɓ������B\n"); c = getchar();
	printf("�����������ɂȂ��镔���炵���A�V��͈ꌩ�^�����ł��邪���ɏ����Ȍ����������B\n"); c = getchar();
	printf("���D�͌������o�����B�ǂ���牮���������ɓ���ɂ͌����K�v�炵���B\n"); c = getchar();
	printf("�u��y�A���̌��ŊJ���Ă����ɂ͂����Ă��Ă����������I�A���ݕ��������Ă���̂ł��I�v\n"); c = getchar();
	printf("���D�̓{�N�����Ɍ���n���A���ݕ��������Ă��܂����B\n"); c = getchar();
	printf("��仁u����ꂽ�ʂ�ɐ�ɓ��낤�����I�v\n"); c = getchar();
	printf("���D�͎󂯎�������Ō����ɓ���񂷂ƓV��̈ꕔ������āA���̒�����A�n�V�S���o�Ă����B\n"); c = getchar();
	printf("�����C�ɂȂ��đ������肽���Z�Z�Z�͐�ɂ͂��������A�{�N���ォ������Ă������B\n"); c = getchar();
	printf("�����̒��͈ٗl�ɐÂ��ŁA�ǂ��ƂȂ��s�C���ȕ��͋C��Y�킹�Ă����B\n"); c = getchar();
	printf("���Â������̒������鋰��i�݂ƁA\n"); c = getchar();
	printf("���D�u���Ƃ��߂łƂ��������܂����I�v\n"); c = getchar();
	printf("�w�p�@�[���I�I�I�x�̉��Ɠ����ɔ��Â���������A�������ł��āA�ڂ������ł��܂����B\n"); c = getchar();
	printf("����͓d�C�̖�����ɂ����̂ł���A�ڂ����ꌩ�n���Ă݂�ƁA�����ɂ͎��D����������̃N���b�J�[�������Ă����B\n"); c = getchar();
	printf("��仁u�т����肵�����[�I�@�S���Ɉ�����I�I�I�@�����I�v\n"); c = getchar();
	printf("��仂ƃ{�N�͂ƂĂ����������A�����ɗ�ÂɂȂ����B\n"); c = getchar();
	printf("���D�u�������Ă��݂܂���I�@�T�v���C�Y���������̂ŁI�v\n"); c = getchar();
	printf("���D�u���ݕ��������Ă����̂Ŋ��t���܂��傤�I�I�v\n"); c = getchar();
	printf("���D�͂ƂĂ����@���ȗl�q�ł��ꂵ�������B���̗l�q���݂Ă��邱�������Ȃ񂾂����ꂵ���B\n"); c = getchar();
	printf("���D�u�ł͐�y�B�̑��Ƃ��j���āI�@�J���p�[�C�I�I�v\n"); c = getchar();
	printf("���D�͂��ꂼ��Ɉ��ݕ���p�ӂ��Ă���A�ꏏ�Ɋ��t�����Ĉ��񂾁B\n"); c = getchar();
	printf("�{�N�����͕�������ꏏ�ɗV�񂾂��Ƃ��O�l�Ō��A����ɐ���オ�����B\n"); c = getchar();
	printf("����ƁA����ɐg�̂��d���Ȃ��Ă���̂��������B\n"); c = getchar();
	printf("�����������Ă���̂��A�����N�O�Ƃ��n�߂��̂��B\n"); c = getchar();
	printf("��u���D�A���ݕ��ɂ��������ꂽ�̂����E�E�H�v\n"); c = getchar();
	printf("�{�N�͎��D�Ɏ��₵�����Ԏ��͋A���Ă��Ȃ��A���C�������΂��Ă����̂��B\n"); c = getchar();
	printf("��仂̕�������Ǝ�仂͂��̊Ԃɂ����œ|��Ď��񂾂悤�ɖ����Ă����̂��B\n"); c = getchar();
	printf("�����I�Ɋ�@�������ď����Ȃ���΂Ȃ�Ȃ��Ɗ������B\n"); c = getchar();
	printf("��u��仁E�E�E�v\n"); c = getchar();
	printf("��仂��N�����Ȃ���΂Ȃ�Ȃ��Ǝv�����O���Ă񂾂��A�Ȃ�Ŏ�仂ƌĂ񂾂̂��킩��Ȃ��Ȃ��Ă��܂����B\n"); c = getchar();
	printf("���񂾂񓪂̒�������ۂɂȂ銴�o�ƂȂ�A���܂ł̎v���o���Ƀz���C�g�m�C�Y���|�������B\n"); c = getchar();
	printf("�{�N�͓��ŉ����l�����Ȃ��Ȃ����B\n"); c = getchar();
	printf("�u�Ȃ�ŁH�v�u�ǂ����āH�v�u�Ȃ��H�v�u���H�v�u�H�H�H�v�u���������������������������������������������������������������������v\n"); c = getchar();
	printf("���������E�E�E�B\n"); c = getchar();
	printf("��u�{�N�͒N�H�v\n"); c = getchar();
	printf("�i�����j\n"); c = getchar();
	printf("���邭�U�����Ă������D���Â��Ɍ��ɗ����Ă����B\n"); c = getchar();
	printf("��u���D�A�{�N�̂�������ȁv\n"); c = getchar();
	printf("�{�N�̎����D���Ȏ��D�̋C�������킩��Ȃ��ӂ�����Ă��܂��Ă����̂��B\n"); c = getchar();
	printf("��仂͂Ȃ����̏󋵂ɂȂ��Ă���̂����킩���Ă͂��Ȃ������B\n"); c = getchar();
	printf("���D�u���͂��Ȃ����D���������v\n"); c = getchar();
	printf("���D�u����΂��Đ�y(���)�̐^�������Ė��邭�����āA�����ł��U������Ăق��������v\n"); c = getchar();
	printf("���D�u�ǂ�Ȃɓw�͂������Ď��͕���Ȃ������v\n"); c = getchar();
	printf("���D�u�^���������Ă킩���Ă��Ă������ł��߂Â��āA���Ȃ��ׂ̗ɂ����������v\n"); c = getchar();
	printf("���D���{�N�ɐU������Ă��炤�Ɗ撣���Ă���̂͒ɂ��قǓ`����Ă����̂��B\n"); c = getchar();
	printf("����𖳎����Ă����񂢂������̂��B\n"); c = getchar();
	printf("��仁u���D�����A�����������̂ˁv\n"); c = getchar();
	printf("��仁u���S�R�C�Â��Ȃ��āA��̎����D���������񂾂ˁv\n"); c = getchar();
	printf("��仁u�ł����߂�ˁv\n"); c = getchar();
	printf("��仁u���͎��D����񂪂ǂꂾ���z���Ă��Ă��A�n���C�͂Ȃ���v\n"); c = getchar();
	printf("��仁u���ꂾ���D���I�v\n"); c = getchar();
	printf("�����͑S�R�D���Ƃ������Ă���Ȃ��������A��仂̓{�N��S�ꈤ���Ă���Ă��邱�Ƃ�`���Ă���A�{�N�͌��ӂ����B\n"); c = getchar();
	printf("��u���D�A���߂�ȁv\n"); c = getchar();
	printf("��u�{�N�͎�仂��D���Ȃ񂾁A�D���Ȃ̂͐��i��������Ȃ���������������ꏏ�ɂ����Ȏv���o������Ă��āA�z���グ�Ă�������A�{�N�͎�仂��������Ȃ��񂾁B�v\n"); c = getchar();
	printf("��u��������`���Ȃ��Ă��߂�ȁv\n"); c = getchar();
	printf("��u��仂̂��ׂĂ��D���ł�����A�ǂ�ȂɎ��Ă悤���֌W�Ȃ��v\n"); c = getchar();
	printf("��u���܂ňꏏ�ɂ������Ԃ���仂ƍ���Ă������̂��A�ȒP�ɂ͕���Ȃ��v\n"); c = getchar();
	printf("��u�����玍�D�ɂ��A�ꏏ�ɒz���グ���p�[�g�i�[��T���Ăق����v\n"); c = getchar();
	printf("��u���i�͑厖�����ǁA���ꂪ���ׂĂ���Ȃ����Ă킩���Ă���͂�����ˁH�v\n"); c = getchar();
	printf("��u������A�{�N�͎��D�̂��Ƃ������Ȃ��v\n"); c = getchar();
	printf("�{�N�͐S�̋��ɂ��܂��Ă������̂����炯�o���Ă��ׂĂ�`�����B\n"); c = getchar();
	printf("���D�u�킩���Ă��܂��v\n"); c = getchar();
	printf("���D�u���ۂɎ�仂���ƂȂ��Đ�y(��)�ɐڂ��Ă��܂������A�����D���ɂ͂Ȃ��Ă���Ȃ����ȂƊ����Ă��܂��܂����v\n"); c = getchar();
	printf("���D�u������ݕ��ɂ���āA�L�����Ȃ������Ă��܂��܂����E�E�E�v\n"); c = getchar();
	printf("���D�u�{���ɂ��߂�Ȃ����v\n"); c = getchar();
	printf("���D�͋����Ȃ��炷�ׂĂ��������Ă��ꂽ�̂��B\n"); c = getchar();
	printf("�{�N�̎��������A��仂̐^�������A���D�͂��ׂĖ��ʂ������Ɗ��������낤���B\n"); c = getchar();
	printf("�{�N�͂����͎v��Ȃ��A���s���ē���ꂽ�o���͐l���̒��őf���炵�����̂�����B\n"); c = getchar();
	printf("���D�ɂ͐V���������ɐi��łق����Ɗ�����B\n"); c = getchar();
	printf("��仁u���v����A���ǉ����Ȃ������񂾂���I�v\n"); c = getchar();
	printf("��仂͂���Ȏ�������Ă����C�Ȋ�Ŏ��D���t�H���[�����̂��B\n"); c = getchar();
	printf("�q��łȂ��悤�Ȏ������ۂɂ������̂ɁA�{�肪�N�����Ƃ͂Ȃ������̂��B\n"); c = getchar();
	printf("���D�͖{����������{�N�������E�����������̂��낤�B\n"); c = getchar();
	printf("���Ƃ������ł������Ƃ��Ă��A�{�N�����͎��D�Ƃ�����l�̐l�Ԃ�ے肵�Ȃ��B\n"); c = getchar();
	printf("Happy END\n"); c = getchar();

	system("cls");

}


void ending2() {

	printf("...?\n"); c = getchar();
	printf("���̕����͈ٗl�ɐÂ��ŁA�ǂ��ƂȂ��s�C���ȕ��͋C��Y�킹�Ă����B\n"); c = getchar();
	printf("���邢�Q���Ɋ���؂��Ă����{�N�̖ڂɂ́A���̔��Â������̒��̓V���G�b�g���炢�ɂ��������Ȃ������B\n"); c = getchar();
	printf("�������A���̗l�ȍ��ׂȈ�ۂ���u�œh��Ԃ����|�I�Ȉ�a���ɁA�{�N�̑S�_�o�͓B�t���ɂȂ����B\n"); c = getchar();
	printf("�����������́A����ȓ����ɖ����Ă����B\n"); c = getchar();

	printf("���܂�̏L���ɓf���C��}�����ꂸ�A�{�N�͂Ƃ����Ɍ�����}����B\n"); c = getchar();
	printf("��u�\�\�E�b�I�@�������c�I�v�@\n"); c = getchar();
	printf("�\���́A���}�ɐ����Ă���l�Ԃ́A�����炭�ꐶ�k�����Ƃ̖����ł��낤����ȏL���������B\n"); c = getchar();
	printf("���R�{�N������ȏL����k���̂͏��߂Ă��B\n"); c = getchar();
	printf("�������A�{�\�I�ɒ�������B\n"); c = getchar();
	printf("����́A���񂾐������̏L�����B\n"); c = getchar();
	printf("���̕����ɂ͐������̎��̂�����B\n"); c = getchar();
	printf("����Ȓ����ɁA�S���܂ꂻ���ɂȂ�B\n"); c = getchar();
	printf("�����āA��݊|����悤�ɁA�ň��̃^�C�~���O�ŕ����̈Â��ɖڂ�����n�߂��B\n"); c = getchar();
	printf("���X�ɖ��炩�ɂȂ��Ă������̌��i�́A�u������������C�����ȁv�@�ƃ{�N���z���������m���A���̂܂܂������蓊�e�������̂悤�ȁA�܂�Ō������̖������̂������B\n"); c = getchar();
	printf("���ɁA�ǂɁA�Ƌ�ɁA�܂�Ńo�P�c�ɓ������y���L���Ԃ��T�������̗l�ɁA�ԍ������݂�͗l�����т���Ă����B\n"); c = getchar();

	printf("�����B\n"); c = getchar();

	printf("���т��������ʂ̂����́A������̑̂��炱�ڂꗎ���Đ����o�̂��낤�B�ԍ����ϐF���A�x�b�g���ƕ����S�̂ɂ��т���Ă����B\n"); c = getchar();

	printf("�i�T����N���[�[�b�g�������ĊJ���j\n"); c = getchar();
	printf("������u�Ђ��c�I�v\n"); c = getchar();
	printf("�N���[�[�b�g�̒��ɂ́A�n�����l�܂��Ă����B\n"); c = getchar();
	printf("�����ɕY���Ă������L�����{�ɂ��Ïk�����悤�ȁA���܂�ɂ��Z�����̓����B\n"); c = getchar();
	printf("���̊C�A��юU����ЁA�X��忂��������v���B\n"); c = getchar();
	printf("�n���̊��̒��g�����̂܂܂Ԃ��T�����l�ȁA�������S�Ȃ��̌��i�̒��ɁA��l�̏����̎��̂���������Ă����B\n"); c = getchar();
	printf("�ꂵ�݂Ɍ��J���ꂽ�ځB�J�����������E�B���ƕ@����͌�������A�葫�͗͂Ȃ����ꉺ�����Ă���B���͌��̐F��������Ȃ����Ɍ��ɐ��܂�A���̑̂ɂ͌�������̂����ł��y���\�𒴂���؂菝�Ǝh���������܂�Ă����B\n"); c = getchar();
	printf("���̐��S�ɉ߂�����i����́A�Ɛl�̂˂΂��悤�Ȉ��ӂƁA�E���ꂽ�����̒n���̗l�ȋꂵ�݂��A���ڃ{�N�̐S�ɗ��ꍞ��ł���悤�ŁA���Ă��邾���ŐS�����Ă��܂��������B\n"); c = getchar();
	printf("�������A�{�N�͂Ȃ������̏����̎��̂���A�ڂ𗣂����Ƃ��ł��Ȃ������B\n"); c = getchar();
	printf("���ɔG�ꂽ�����̊������B\n"); c = getchar();
	printf("�ӂƁA����ł���͂��̏����Ɩڂ��������C�������B\n"); c = getchar();
	printf("�u�ԁB\n"); c = getchar();
	printf("���ߐ؂��Ă����J�[�e������C�ɊJ�����悤�ɁA�L���̈Â������ꏊ�S�ĂɌ���������A�{�N�́A�S�Ă��v���o�����B\n"); c = getchar();
	printf("�u�����ƈ�l�ł���ȈÂ��Ƃ���Ɂc�B�@�₵��������ȁB�@�ɂ�������ȁB�@�Y��Ă��߂�ȁc�B�w������x�c�I�v\n"); c = getchar();
	printf("�ǂ�Ȏ��ł��Ί炾�������z�̂悤�Ȕޏ��B\n"); c = getchar();
	printf("�o����������炸���ƕς�炸�A�{�N�̂��Ƃ� �w�L�~�x �ƌĂԔޏ��B\n"); c = getchar();
	printf("�a�����Ƀv���[���g�����Ђ܂��̃w�A�s�����A���������ɂ����t���Ă����ޏ��B\n"); c = getchar();
	printf("���ׂ̍��̂��A�؂ꖡ�̈������ȃt���[�c�i�C�t�ŉ��x�����x���˂��h����Ȃ���A�����̕�������ۂǒɂ����낤�ɁA�ꂵ�����낤�ɁA����ȏ󋵂ŁA��Ȃ��������Ȃ��Ȃ����{�N�̎���S�z�����Ɍ��߂Ă����ޏ��B\n"); c = getchar();

	printf("����Ȕޏ��̂��Ƃ��A����Ȃɑ�D���������A��؂������ޏ��̂��Ƃ��A���낤���Ƃ����S�ɖY��Ă����A�����ŏ�Ȃ������ɑ΂��āA�{�肪�N���オ��B\n"); c = getchar();
	printf("�����āA�����Ȃ��l�Ԃ͂�����l�����B\n"); c = getchar();
	printf("�u���O�́c�B�@���O�̂��Ƃ����͐�΂ɋ����Ȃ��c�I�v\n"); c = getchar();
	printf("	�[���{��Ƒ����݂����߂āA�Y��Ă������̖��O��ꂭ�B\n"); c = getchar();
	printf("�u�����Ȃ����c�B�@�w���D�x�c�I�v\n"); c = getchar();

	printf("�u�S���v���o���Ă��܂��܂������c�B�@�c�O�ł��w��y�x�v\n"); c = getchar();

	printf("�U��Ԃ�ƁA�����ɂ͈����������Ă����B\n"); c = getchar();
	printf("��������E���A�{�N�̋L����D���A���낤���Ƃ��w������x�ɐ�����낤�Ƃ����A�����̂悤�Ȃ��̏����A�w���D�x���A�ׂ��O�����̂悤�ȁA�C�����̈����΂݂����̊�ɓ\��t���Ȃ���A�Â��ɗ����Ă����B\n"); c = getchar();
	printf("�����l���Ă��Ȃ������B\n"); c = getchar();
	printf("�ڂ̑O�ɗ����Ă��鎍�D���������Ă��悤���ǂ��ł������B\n"); c = getchar();
	printf("�����������D������ŉ���ŎE�������āA�����ł��Ȃ������{�N�̓O�Y�ł̂�܂Ŏ���ł������B\n"); c = getchar();
	printf("�����I����Ă������B���ׂĂȂ��Ȃ��Ă��܂��΂����̂ɁB\n"); c = getchar();

	printf("�������I�I\n"); c = getchar();

	printf("�����h�������̂��A�����̌�������Ă���̂��������B\n"); c = getchar();
	printf("����ŁA��仂Ɠ����ɂȂꂽ�B\n"); c = getchar();
	printf("�{�N�͏����΂݂𕂂��ׂȂ����o�̂悤�ɏ����Ă����B\n"); c = getchar();
	printf("���ˎ��ˎ��ˎ��ˎ��ˎ��ˁE�E�E�E�B\n"); c = getchar();
	printf("�M�����I�I\n"); c = getchar();
	printf("�{�N�͎��D�̊���܂����Ɍ����u�Ԕ��˓I�Ɏ��D�̎��Ў�Œ��ߕt�����B\n"); c = getchar();
	printf("���D�͒�R���悤�Ɛn���ő̂��a����Ă��邪�A�ɂ��Ȃ��B\n"); c = getchar();
	printf("�ʂɋ������Ă���킯����Ȃ��A�ǂ��ł������E�E�E�B\n"); c = getchar();
	printf("�u�͂₭���˂΂����̂Ɂv\n"); c = getchar();
	printf("���̊Ԃɂ����D�̔��R�͎~��ł����B\n"); c = getchar();
	printf("�{�N�͎���i�߂Ă�����������B\n"); c = getchar();
	printf("�����ł��Ȃ��Ď���ł����B\n"); c = getchar();
	printf("���̂܂ɂ����D�̊��g�̂��{���ł��A��������Ă����B\n"); c = getchar();
	printf("�C�Â��Ȃ������ɋ󂢂Ă���Ў�ŉ����Ă����̂��낤�B\n"); c = getchar();
	printf("�o���Ă��Ȃ����ǂ��ł������B\n"); c = getchar();
	printf("����ł�B\n"); c = getchar();
	printf("�o�^���b�I�I\n"); c = getchar();
	printf("�{�N�̓|�ꂽ��͋󂢂��N���[�[�b�g�̖ڂ̑O�������B\n"); c = getchar();
	printf("�Ō�̗͂�U��i��A�̂���������Ȃ���{�N�͎�仂̂΂ɂ��Ă�ꂽ�B\n"); c = getchar();
	printf("...\n"); c = getchar();
	printf("<<<<<<<<<<<<<���G���f�B���O>>>>>>>>>>>>\n"); c = getchar();
	system("cls");
}


void ending3() {
	printf("���̕����͈ٗl�ɐÂ��ŁA�ǂ��ƂȂ��s�C���ȕ��͋C��Y�킹�Ă����B\n"); c = getchar();
	printf("���邢�Q���Ɋ���Ă����{�N�̖ڂɂ́A���̔��Â������̒��̓V���G�b�g���炢�ɂ��������Ȃ������B\n"); c = getchar();
	printf("�������A���̗l�ȍ��ׂȈ�ۂ���u�œh��Ԃ����|�I�Ȉ�a���ɁA�{�N�̑S�_�o�͓B�t���ɂȂ����B\n"); c = getchar();

	printf("�\�\���L���B\n"); c = getchar();

	printf("���܂�̏L���ɓf���C��}�����ꂸ�A�{�N�͂Ƃ����Ɏ�Ō���}����B\n"); c = getchar();
	printf("������u�\�\�E�b�I�@�������c�I�v�@\n"); c = getchar();
	printf("�\���͕��}�ɐ����Ă���l�Ԃ͈ꐶ�k�����Ƃ̖����ł��낤����ȏL���������B\n"); c = getchar();
	printf("���R�{�N������ȏL����k���̂͏��߂Ă��B\n"); c = getchar();
	printf("�������A�{�\�I�ɒ�������B\n"); c = getchar();
	printf("����́A�����������񂾏L���B�@\n"); c = getchar();
	printf("���L���B\n"); c = getchar();
	printf("�����āA��݊|����悤�ɁA�ň��̃^�C�~���O�ŕ����̈Â��ɖڂ�����n�߂��B\n"); c = getchar();
	printf("���X�ɖ��炩�ɂȂ������̌��i�́A�����ɖ����镅�L����A�u������������C�����ȁv�Ƒz���������i�����̂܂ܓ��e�������̂悤�ȁA�܂�Ō������̖������̂������B\n"); c = getchar();
	printf("���ɁA�ǂɁA�Ƌ�ɁA�܂�Ńo�P�c�ɓ������y���L���Ԃ��T�������̗l�ɁA�ԍ������݂�͗l�����т���Ă����B\n"); c = getchar();

	printf("�����B\n"); c = getchar();

	printf("���т��������ʂ̂����́A������̑̂��炱�ڂꗎ���Đ����o�̂��낤�B�ԍ����ϐF���A�x�b�g���ƕ����S�̂ɂ��т���Ă����B\n"); c = getchar();

	printf("������u���c�@�����c�v\n"); c = getchar();
	printf("���܂�̎S���O�ɑS�g�̗͂������A���̏�ɂւ��荞��ł��܂����B\n"); c = getchar();
	printf("�����^�����ɂȂ�B\n"); c = getchar();
	printf("�{�N�͂ǂ����Ă���ȋ��낵���Ƃ���ɋ���񂾂낤�B\n"); c = getchar();
	printf("�����Ȃ���΁B\n"); c = getchar();
	printf("���̋��낵�����~����B�ޏ�����B�����Ă��̓��̂̒m��Ȃ��L���̎c�[����B\n"); c = getchar();
	printf("���Ȃ����ŁA�����Ȃ��̂ŁA����ł��Ƃɂ��������Ȃ���΂ƁA�C�͂�U��i�藧���オ��B\n"); c = getchar();
	printf("���Ă��B�܂��ޏ��͋A���Ă��Ȃ��B���̂����ɓ����悤�B\n"); c = getchar();
	printf("�u�_������v\n"); c = getchar();

	printf("��l�Ɏv���o�����̂́A���������A�����傫�ȃn�`�ɘr���h���ꂽ���́A���̊��o�������B\n"); c = getchar();
	printf("�Ȃ�Ƃ������Ȃ��C���ȔM���B�̓��ɔM�����������˂����܂ꂽ�悤�ȁA�ς���C���������B\n"); c = getchar();
	printf("�w���𒆐S�ɁA�̂͂ƂĂ��M���̂ɁA���̒��̓X�b�Ɨ₽���Ȃ�A���Ȋ��o�B�@����B\n"); c = getchar();

	printf("���ɁB\n"); c = getchar();

	printf("������u�����b�I�H�@�����I�I�H�@���������b�I�I�I�I�v\n"); c = getchar();
	printf("�\�\�ɂ��ɂ��C�^�C�C�^�C�C�^�C������������\n"); c = getchar();
	printf("�w���ɉ������h�������H�@�h���ꂽ�H�@�N�ɁH�@�Ȃ�ŁH\n"); c = getchar();

	printf("���܂�̌��ɂ̂������܂�A�]�����B\n"); c = getchar();
	printf("���E�Ɠ��͖\�����A���M���A���������ł���B\n"); c = getchar();
	printf("�u�L�A�L�~�̓b�c�I�@�ǂ����c�āc�@�Ȃ�c�Łc�c�v\n"); c = getchar();
	printf("�Ԃ��h��Ԃ���Ă������E�̒[�ŁA�A�J�����l�`�̗l�Ȗ��\��Ń{�N�������낵�Ă����B\n"); c = getchar();
	printf("���̖ڂ͉�ꂽ�ߋ�𒭂߂�q���̂悤�ȁA���@���ŋ󋕂ȃ��m�������B\n"); c = getchar();
	printf("�Ԃ����܂肫�����{�N�̎��E�́A���̕����ŎE���ꂽ�ł��낤�N���̌��Ɠ����悤�ɁA���X�ɍ����Ȃ��Ă䂫�A�₪�čŏ����牽�������������̗l�ɁA���������^�����ɐ��܂����B\n"); c = getchar();
	printf("\n");
	printf("�L�������߂����Ƃ͂ł��Ȃ������B\n"); c = getchar();
	printf("<<<<<<<<<<<<<�o�b�g�G���f�B���O>>>>>>>>>>>>\n"); c = getchar();

	system("cls");

}


void ending4() {

	printf("�����肪�A���Ă����A���ւ̉������������B\n"); c = getchar();
	printf("���ւɌ}���ɍs�����B\n"); c = getchar();
	printf("������u�������܁I�v\n"); c = getchar();
	printf("������u��������v\n"); c = getchar();
	printf("������u�����ς��H�ޔ����Ă�������I�v\n"); c = getchar();
	printf("������u�����̔ӌ�т͌N���D���������n���o�[�O���I�v\n"); c = getchar();
	printf("�{�N�͉����v���o���Ȃ����n���o�[�O���D���������񂾂ȁB\n"); c = getchar();
	printf("������u��`����v\n"); c = getchar();
	printf("������u���肪�Ɓ`�I�v\n"); c = getchar();
	printf("���ꂩ��A�O�N�B���܂��L���͖߂�Ȃ����y���������ɓ����ł���B\n"); c = getchar();
	printf("������Ƃ͌������āA�q������낤�ƍl���Ă���B\n"); c = getchar();
	printf("�N���厖�Ȑl��Y��Ă���悤�ȋC�����邪�A�C�̂������낤�B\n"); c = getchar();
	printf("<<<<<<<<<<<<<�G���f�B���O>>>>>>>>>>>>\n"); c = getchar();
	system("cls");

}