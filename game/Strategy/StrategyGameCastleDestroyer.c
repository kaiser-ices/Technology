#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <time.h>

#define	MAP_WIDTH			17			// �Ղ̉�
#define	MAP_LENGTH			17			// �Ղ̏c

#define TOTAL_PIECE_NUMBER	16			// ��̐�
#define MOVABLE_PIECENO		7			// ���������̐�

#define PLAYER				0			// �v���C���[
#define COMPUTER			1			// COM

// �}�X�̐F
#define COLOR_BLOCK			0			// �ړ��s�\�̃}�X�͍�
#define COLOR_SAND			14*16		// ���n�̃}�X�͉��F
#define COLOR_GRASS			2*16		// ���n�̃}�X�͗�
#define COLOR_ROCK			12*16		// ���̃}�X�͐�
#define COLOR_RESET			15			// �}�X�̐F�����Z�b�g
#define COLOR_RANGE			9*16		// �ړ��͈͂̃}�X�͐�
#define MOVED_COLOR			13			// ��������͎�

// ���ID
#define COM_CASTLE_ID		1
#define COM_KNIGHT_ID		2
#define COM_SOLDIER1_ID		3
#define COM_SOLDIER2_ID		4
#define COM_SOLDIER3_ID		5
#define COM_SOLDIER4_ID		6
#define COM_ARCHER1_ID		7
#define COM_ARCHER2_ID		8
#define PLAYER_CASTLE_ID	9
#define PLAYER_KNIGHT_ID	10
#define PLAYER_SOLDIER1_ID	11
#define PLAYER_SOLDIER2_ID	12
#define PLAYER_SOLDIER3_ID	13
#define PLAYER_SOLDIER4_ID	14
#define PLAYER_ARCHER1_ID	15
#define PLAYER_ARCHER2_ID	16

// ��̃q�b�g�|�C���g
#define CASTLE_HITPOINT		150
#define KNIGHT_HITPOINT		100
#define SOLDIER_HITPOINT	80
#define ARCHER_HITPOINT		50

// ��̍U����
#define CASTLE_ATTACK		90
#define KNIGHT_ATTACK		65
#define SOLDIER_ATTACK		50
#define ARCHER_ATTACK		40

// ��̖h���
#define CASTLE_DEFENSE		30
#define KNIGHT_DEFENSE		50
#define SOLDIER_DEFENSE		40
#define ARCHER_DEFENSE		35

// ��̈ړ���
#define CASTLE_MOVPOWER		1
#define KNIGHT_MOVPOWER		8
#define SOLDIER_MOVPOWER	5
#define ARCHER_MOVPOWER		5

// ��̏󋵂�ۊǂ��邽�߂̃}�X�N
#define ALIVE_MASK			0x0001
#define MOVED_MASK			0x0002
#define COM_PIECE_MASK		0x0004

// �n�`�ɂ���Ă̈ړ���
#define SAND_ABILITY		0
#define GRASS_ABILITY		5
#define ROCK_ABILITY		30

// �Q�[���̏�
#define COM_TO_MOVE			1
#define PLAYER_TO_MOVE		2
#define COM_WINS			3
#define PLAYER_WINS			4

#define WEAK_CASTLE			50		// �ア��̏ꍇ�ɉ񕜂ł��Ȃ�
#define RECOVERY_RATE		10		// �񕜗�

#define MIN_DISTANCE		0		// �ŒZ����
#define MAX_DISTANCE		99		// �ő勗��

// �n�`���̂��߂̒萔
enum{
	SQ_BLOCK = 0,		// �ړ��s�\
	SQ_GRASS,			// ���n
	SQ_SAND,			// ���n
	SQ_ROCK,			// ���
	SQ_END
};

//��̎��
enum{
	PIECE_CASTLE = 0,	// ��
	PIECE_SOLDIER,		// ����
	PIECE_ARCHER,		// �|��
	PIECE_KNIGHT,		// �R��
	PIECE_END
};

// ��̏��
typedef struct Piece {
	int	x;				// x���W
	int y;				// y���W
	int	hitPoint;		// �q�b�g�|�C���g
	int	movPow;			// �ړ���
	int	attack;			// �U����
	int	defense;		// �h���
	int	pieceType;		// ��̎��
	int	status;			// ���
} PIECE;

//------------------------------------------------------------�n�}�f�[�^
const int terrainMap[MAP_WIDTH][MAP_LENGTH] = {
	SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK,
	SQ_BLOCK, SQ_SAND, SQ_SAND, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_ROCK, SQ_SAND, SQ_ROCK, SQ_BLOCK, SQ_BLOCK, SQ_ROCK, SQ_SAND, SQ_SAND, SQ_SAND, SQ_SAND, SQ_BLOCK,
	SQ_BLOCK, SQ_SAND, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_ROCK, SQ_SAND, SQ_ROCK, SQ_ROCK, SQ_ROCK, SQ_SAND, SQ_SAND, SQ_SAND, SQ_SAND, SQ_GRASS, SQ_BLOCK,
	SQ_BLOCK, SQ_SAND, SQ_GRASS, SQ_GRASS, SQ_BLOCK, SQ_SAND, SQ_GRASS, SQ_SAND, SQ_SAND, SQ_SAND, SQ_SAND, SQ_SAND, SQ_BLOCK, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_BLOCK,
	SQ_BLOCK, SQ_GRASS, SQ_GRASS, SQ_ROCK, SQ_BLOCK, SQ_SAND, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_SAND, SQ_SAND, SQ_SAND, SQ_BLOCK, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_BLOCK,
	SQ_BLOCK, SQ_ROCK, SQ_GRASS, SQ_ROCK, SQ_ROCK, SQ_SAND, SQ_SAND, SQ_GRASS, SQ_GRASS, SQ_SAND, SQ_SAND, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_BLOCK,
	SQ_BLOCK, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_ROCK, SQ_GRASS, SQ_ROCK, SQ_GRASS, SQ_GRASS, SQ_SAND, SQ_SAND, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_BLOCK,
	SQ_BLOCK, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_ROCK, SQ_SAND, SQ_SAND, SQ_SAND, SQ_SAND, SQ_ROCK, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_BLOCK,
	SQ_BLOCK, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_ROCK, SQ_ROCK, SQ_SAND, SQ_SAND, SQ_SAND, SQ_ROCK, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_BLOCK,
	SQ_BLOCK, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_ROCK, SQ_ROCK, SQ_ROCK, SQ_SAND, SQ_BLOCK, SQ_SAND, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_BLOCK,
	SQ_BLOCK, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_BLOCK, SQ_GRASS, SQ_SAND, SQ_SAND, SQ_SAND, SQ_BLOCK, SQ_GRASS, SQ_BLOCK, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_BLOCK,
	SQ_BLOCK, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_BLOCK, SQ_GRASS, SQ_SAND, SQ_SAND, SQ_SAND, SQ_SAND, SQ_GRASS, SQ_BLOCK, SQ_BLOCK, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_BLOCK,
	SQ_BLOCK, SQ_GRASS, SQ_GRASS, SQ_SAND, SQ_BLOCK, SQ_SAND, SQ_SAND, SQ_SAND, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_BLOCK,
	SQ_BLOCK, SQ_GRASS, SQ_SAND, SQ_SAND, SQ_SAND, SQ_SAND, SQ_SAND, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_BLOCK,
	SQ_BLOCK, SQ_SAND, SQ_SAND, SQ_SAND, SQ_GRASS, SQ_ROCK, SQ_SAND, SQ_SAND, SQ_BLOCK, SQ_BLOCK, SQ_SAND, SQ_BLOCK, SQ_ROCK, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_BLOCK,
	SQ_BLOCK, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_GRASS, SQ_ROCK, SQ_SAND, SQ_SAND, SQ_SAND, SQ_SAND, SQ_ROCK, SQ_BLOCK, SQ_ROCK, SQ_ROCK, SQ_SAND, SQ_BLOCK, SQ_BLOCK,
	SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK, SQ_BLOCK
};

int pieceMap[MAP_LENGTH][MAP_WIDTH];	//	��̏ꏊ
PIECE gamePieces[TOTAL_PIECE_NUMBER + 1];	// ��̏��̊Ǘ�

int gameStatus;				// �Q�[���̏󋵁i��ԁA�I���j
int piecesToMove;			// �܂��������Ă��Ȃ���̐�
int playerAlivePieceNo;		// �v���C���[���̐����Ă����̐�
int comAlivePieceNo;		// COM���̐����Ă����̐�
int playerCastleDestroyed;	// �v���C���[�̏邪���󂩂ǂ���
int comCastleDestroyed;		// COM�̏邪���󂩂ǂ���

int	moveRange[MAP_LENGTH][MAP_WIDTH];	//�ړ��\�͈͂Ȃǂ̃`�F�b�N�p
int	tmpMap[MAP_LENGTH][MAP_WIDTH];

//-----------------------------------------------------------------------------�ړ��ɕK�v�ȃR�X�g
int	moveCost[PIECE_END][SQ_END + 1] = {
	{ 99, 99, 99, 99 },		//��͓����Ȃ�
	{ 99, 1, 1, 2 },		//����
	{ 99, 1, 2, 4 },		//�|��
	{ 99, 1, 3, 4 },		//�R��
};

//-----------------------------------------------------------------------------��̑���
//�@�i��E�����E�|���E�R�m�j[�U����][���葤]
int	pieceCompatibility[PIECE_END][PIECE_END] = {
	{ 0, 0, 0, 15 },		//��
	{ 0, 0, -25, 25 },		//����
	{ 0, 25, 0, -50 },		//�|��
	{ -15, -25, 50, 0 }, 		//�R��
};

//�n�`���ʂ̒l�i�i���s�\�E���n�E���n�E���j
int	groundPower[SQ_END] = { 0, 5, 0, 30 };

// �֐��̐錾
void initPieces();
void showMapWithPieces();
void showSquareInfo(int, int, int);
void displayCoordinates(int, int);
void selectAndMovePlayerPiece();
void getPlayerPiece(int *, int *);

void findMoveRange(int, int, const PIECE *, int);
void excludePiece(int, int);
void checkRange(int, int, int, int, int[][MAP_WIDTH]);
void checkDistance(int, int, int, int, int[][MAP_WIDTH]);
void fillMap(int[][MAP_WIDTH], int);
void showMoveRange();
void showPieceStatus();
void getPlayerDestination(int, int *, int *);
int flip(int);
void nextToCastleRecovery(int);
int getFullHitPointsForPiece(int);
void resolveBattle(PIECE *, int);
int selectOpponent(PIECE *, int);
void fightBattle(PIECE *, int);
int updateBattleHitPoints(int, int, int, int);

void moveComPieces();
void decideComPieceDestination(int, int *, int *);
void cpuCastleDestroyer(int, int *, int *);


int main()
{

	char c, userSelection;

	srand((unsigned)time(NULL));	//�����_�}�C�Y�i�����̏������j

	initPieces();	// ��̏���������

	gameStatus = PLAYER_TO_MOVE;	// �v���C���[�̎��
	playerAlivePieceNo = comAlivePieceNo = MOVABLE_PIECENO;	// ���ׂĂ̋�͐����Ă���
	playerCastleDestroyed = comCastleDestroyed = 0;			// ��͂܂����󂳂�Ă��Ȃ�
	piecesToMove = playerAlivePieceNo;	// �v���C���[���܂��������Ă��Ȃ���̐�

	printf("===================================\n");
	printf("Simple console based strategy game.\n");
	printf("===================================\n");

	while (1)
	{
		showMapWithPieces();	// �Ղ�\��

		if (gameStatus == PLAYER_TO_MOVE) // �v���C���[�̎��
		{
			// ���[���@���j��
			printf("Possible actions:\n");
			printf("1) Select piece to move\n");
			printf("2) Show complete piece status\n");
			printf("N) Start new game\n");
			printf("Q) Quit program\n");
			printf("Please enter your selection: ");

			c = getchar();
			userSelection = c;

			while ((c = getchar()) != '\n')
				;

			switch (userSelection)
			{
			case '1':
				selectAndMovePlayerPiece();	// �v���C���[�̋�𓮂���
				break;
			case '2':
				showPieceStatus();	// ��̏���\��
				break;
			case 'N':	// �Q�[�����ăX�^�[�g
				initPieces();
				playerAlivePieceNo = comAlivePieceNo = MOVABLE_PIECENO;
				playerCastleDestroyed = comCastleDestroyed = 0;
				piecesToMove = playerAlivePieceNo;
				break;
			case 'Q':	// �v���O�������I��
				return 0;
			default:
				break;
			}

		}
		else if (gameStatus == COM_WINS) // COM�̏����錾�Ə�����
		{
			if (playerCastleDestroyed)
				printf("\n\nI DESTROYED YOUR CASTLE!\n");
			else if (playerAlivePieceNo == 0)
				printf("\n\nI KILLED YOUR ARMY!\n");
			printf("\n\nYOU LOSE!!\n\n");
			printf("Want to try again?\n\n");
			initPieces();
			gameStatus = PLAYER_TO_MOVE;
			playerAlivePieceNo = comAlivePieceNo = MOVABLE_PIECENO;
			playerCastleDestroyed = comCastleDestroyed = 0;
			piecesToMove = playerAlivePieceNo;
		}
		else if (gameStatus == PLAYER_WINS) // COM�̕����錾�Ə�����
		{
			if (comCastleDestroyed)
				printf("\n\nYou destroyed my castle...\n");
			else if (comAlivePieceNo == 0)
				printf("\n\nYou killed my army...\n");
			printf("\n\nYOU WIN!!\n\n");
			printf("Want to try again?\n\n");
			initPieces();
			gameStatus = PLAYER_TO_MOVE;
			playerAlivePieceNo = comAlivePieceNo = MOVABLE_PIECENO;
			playerCastleDestroyed = comCastleDestroyed = 0;
			piecesToMove = playerAlivePieceNo;
		}
		else {
			moveComPieces(); // COM�̋�𓮂���
		}

	}
	return 0;
}

// ��̏ꏊ�Ɠ�����������
void initPieces()
{

	int x, y;

	for (x = 1; x < MAP_LENGTH - 1; x++)
	for (y = 1; y < MAP_WIDTH - 1; y++)
		pieceMap[x][y] = 0;

	// COM�̋�
	pieceMap[8][1] = COM_CASTLE_ID;									// ���̋�̏ꏊ
	gamePieces[COM_CASTLE_ID].x = 8;									// ���̋�̏ꏊ������ɂ��ۊ�
	gamePieces[COM_CASTLE_ID].y = 1;									// ���̋�̏ꏊ������ɂ��ۊ�
	gamePieces[COM_CASTLE_ID].hitPoint = CASTLE_HITPOINT;				// ���̋�̃q�b�g�|�C���g
	gamePieces[COM_CASTLE_ID].pieceType = PIECE_CASTLE;				// ���̋�̎��
	gamePieces[COM_CASTLE_ID].attack = CASTLE_ATTACK;					// ���̋�̍U����
	gamePieces[COM_CASTLE_ID].defense = CASTLE_DEFENSE;				// ���̋�̖h���
	gamePieces[COM_CASTLE_ID].movPow = CASTLE_MOVPOWER;				// ���̋�̈ړ���
	gamePieces[COM_CASTLE_ID].status = ALIVE_MASK | COM_PIECE_MASK;	// ���̋�͐����Ă���COM�̋�A��͓����Ȃ�

	pieceMap[8][2] = COM_KNIGHT_ID;
	gamePieces[COM_KNIGHT_ID].x = 8;
	gamePieces[COM_KNIGHT_ID].y = 2;
	gamePieces[COM_KNIGHT_ID].hitPoint = KNIGHT_HITPOINT;
	gamePieces[COM_KNIGHT_ID].pieceType = PIECE_KNIGHT;
	gamePieces[COM_KNIGHT_ID].attack = KNIGHT_ATTACK;
	gamePieces[COM_KNIGHT_ID].defense = KNIGHT_DEFENSE;
	gamePieces[COM_KNIGHT_ID].movPow = KNIGHT_MOVPOWER;
	gamePieces[COM_KNIGHT_ID].status = ALIVE_MASK | MOVED_MASK | COM_PIECE_MASK;	// ���̋�͐����Ă���COM�̋�A�ŏ��̓v���C���[�̎�Ԃ̂Łu�������v��

	pieceMap[6][2] = COM_SOLDIER1_ID;
	gamePieces[COM_SOLDIER1_ID].x = 6;
	gamePieces[COM_SOLDIER1_ID].y = 2;
	gamePieces[COM_SOLDIER1_ID].hitPoint = SOLDIER_HITPOINT;
	gamePieces[COM_SOLDIER1_ID].pieceType = PIECE_SOLDIER;
	gamePieces[COM_SOLDIER1_ID].attack = SOLDIER_ATTACK;
	gamePieces[COM_SOLDIER1_ID].defense = SOLDIER_DEFENSE;
	gamePieces[COM_SOLDIER1_ID].movPow = SOLDIER_MOVPOWER;
	gamePieces[COM_SOLDIER1_ID].status = ALIVE_MASK | MOVED_MASK | COM_PIECE_MASK;

	pieceMap[7][2] = COM_SOLDIER2_ID;
	gamePieces[COM_SOLDIER2_ID].x = 7;
	gamePieces[COM_SOLDIER2_ID].y = 2;
	gamePieces[COM_SOLDIER2_ID].hitPoint = SOLDIER_HITPOINT;
	gamePieces[COM_SOLDIER2_ID].pieceType = PIECE_SOLDIER;
	gamePieces[COM_SOLDIER2_ID].attack = SOLDIER_ATTACK;
	gamePieces[COM_SOLDIER2_ID].defense = SOLDIER_DEFENSE;
	gamePieces[COM_SOLDIER2_ID].movPow = SOLDIER_MOVPOWER;
	gamePieces[COM_SOLDIER2_ID].status = ALIVE_MASK | MOVED_MASK | COM_PIECE_MASK;

	pieceMap[9][2] = COM_SOLDIER3_ID;
	gamePieces[COM_SOLDIER3_ID].x = 9;
	gamePieces[COM_SOLDIER3_ID].y = 2;
	gamePieces[COM_SOLDIER3_ID].hitPoint = SOLDIER_HITPOINT;
	gamePieces[COM_SOLDIER3_ID].pieceType = PIECE_SOLDIER;
	gamePieces[COM_SOLDIER3_ID].attack = SOLDIER_ATTACK;
	gamePieces[COM_SOLDIER3_ID].defense = SOLDIER_DEFENSE;
	gamePieces[COM_SOLDIER3_ID].movPow = SOLDIER_MOVPOWER;
	gamePieces[COM_SOLDIER3_ID].status = ALIVE_MASK | MOVED_MASK | COM_PIECE_MASK;

	pieceMap[10][2] = COM_SOLDIER4_ID;
	gamePieces[COM_SOLDIER4_ID].x = 10;
	gamePieces[COM_SOLDIER4_ID].y = 2;
	gamePieces[COM_SOLDIER4_ID].hitPoint = SOLDIER_HITPOINT;
	gamePieces[COM_SOLDIER4_ID].pieceType = PIECE_SOLDIER;
	gamePieces[COM_SOLDIER4_ID].attack = SOLDIER_ATTACK;
	gamePieces[COM_SOLDIER4_ID].defense = SOLDIER_DEFENSE;
	gamePieces[COM_SOLDIER4_ID].movPow = SOLDIER_MOVPOWER;
	gamePieces[COM_SOLDIER4_ID].status = ALIVE_MASK | MOVED_MASK | COM_PIECE_MASK;

	pieceMap[7][1] = COM_ARCHER1_ID;
	gamePieces[COM_ARCHER1_ID].x = 7;
	gamePieces[COM_ARCHER1_ID].y = 1;
	gamePieces[COM_ARCHER1_ID].hitPoint = ARCHER_HITPOINT;
	gamePieces[COM_ARCHER1_ID].pieceType = PIECE_ARCHER;
	gamePieces[COM_ARCHER1_ID].attack = ARCHER_ATTACK;
	gamePieces[COM_ARCHER1_ID].defense = ARCHER_DEFENSE;
	gamePieces[COM_ARCHER1_ID].movPow = ARCHER_MOVPOWER;
	gamePieces[COM_ARCHER1_ID].status = ALIVE_MASK | MOVED_MASK | COM_PIECE_MASK;

	pieceMap[9][1] = COM_ARCHER2_ID;
	gamePieces[COM_ARCHER2_ID].x = 9;
	gamePieces[COM_ARCHER2_ID].y = 1;
	gamePieces[COM_ARCHER2_ID].hitPoint = ARCHER_HITPOINT;
	gamePieces[COM_ARCHER2_ID].pieceType = PIECE_ARCHER;
	gamePieces[COM_ARCHER2_ID].attack = ARCHER_ATTACK;
	gamePieces[COM_ARCHER2_ID].defense = ARCHER_DEFENSE;
	gamePieces[COM_ARCHER2_ID].movPow = ARCHER_MOVPOWER;
	gamePieces[COM_ARCHER2_ID].status = ALIVE_MASK | MOVED_MASK | COM_PIECE_MASK;

	// �v���C���[�̋�
	pieceMap[8][15] = PLAYER_CASTLE_ID;
	gamePieces[PLAYER_CASTLE_ID].x = 8;
	gamePieces[PLAYER_CASTLE_ID].y = 15;
	gamePieces[PLAYER_CASTLE_ID].hitPoint = CASTLE_HITPOINT;
	gamePieces[PLAYER_CASTLE_ID].pieceType = PIECE_CASTLE;
	gamePieces[PLAYER_CASTLE_ID].attack = CASTLE_ATTACK;
	gamePieces[PLAYER_CASTLE_ID].defense = CASTLE_DEFENSE;
	gamePieces[PLAYER_CASTLE_ID].movPow = CASTLE_MOVPOWER;
	gamePieces[PLAYER_CASTLE_ID].status = ALIVE_MASK;

	pieceMap[8][14] = PLAYER_KNIGHT_ID;
	gamePieces[PLAYER_KNIGHT_ID].x = 8;
	gamePieces[PLAYER_KNIGHT_ID].y = 14;
	gamePieces[PLAYER_KNIGHT_ID].hitPoint = KNIGHT_HITPOINT;
	gamePieces[PLAYER_KNIGHT_ID].pieceType = PIECE_KNIGHT;
	gamePieces[PLAYER_KNIGHT_ID].attack = KNIGHT_ATTACK;
	gamePieces[PLAYER_KNIGHT_ID].defense = KNIGHT_DEFENSE;
	gamePieces[PLAYER_KNIGHT_ID].movPow = KNIGHT_MOVPOWER;
	gamePieces[PLAYER_KNIGHT_ID].status = ALIVE_MASK;

	pieceMap[6][14] = PLAYER_SOLDIER1_ID;
	gamePieces[PLAYER_SOLDIER1_ID].x = 6;
	gamePieces[PLAYER_SOLDIER1_ID].y = 14;
	gamePieces[PLAYER_SOLDIER1_ID].hitPoint = SOLDIER_HITPOINT;
	gamePieces[PLAYER_SOLDIER1_ID].pieceType = PIECE_SOLDIER;
	gamePieces[PLAYER_SOLDIER1_ID].attack = SOLDIER_ATTACK;
	gamePieces[PLAYER_SOLDIER1_ID].defense = SOLDIER_DEFENSE;
	gamePieces[PLAYER_SOLDIER1_ID].movPow = SOLDIER_MOVPOWER;
	gamePieces[PLAYER_SOLDIER1_ID].status = ALIVE_MASK;

	pieceMap[7][14] = PLAYER_SOLDIER2_ID;
	gamePieces[PLAYER_SOLDIER2_ID].x = 7;
	gamePieces[PLAYER_SOLDIER2_ID].y = 14;
	gamePieces[PLAYER_SOLDIER2_ID].hitPoint = SOLDIER_HITPOINT;
	gamePieces[PLAYER_SOLDIER2_ID].pieceType = PIECE_SOLDIER;
	gamePieces[PLAYER_SOLDIER2_ID].attack = SOLDIER_ATTACK;
	gamePieces[PLAYER_SOLDIER2_ID].defense = SOLDIER_DEFENSE;
	gamePieces[PLAYER_SOLDIER2_ID].movPow = SOLDIER_MOVPOWER;
	gamePieces[PLAYER_SOLDIER2_ID].status = ALIVE_MASK;

	pieceMap[9][14] = PLAYER_SOLDIER3_ID;
	gamePieces[PLAYER_SOLDIER3_ID].x = 9;
	gamePieces[PLAYER_SOLDIER3_ID].y = 14;
	gamePieces[PLAYER_SOLDIER3_ID].hitPoint = SOLDIER_HITPOINT;
	gamePieces[PLAYER_SOLDIER3_ID].pieceType = PIECE_SOLDIER;
	gamePieces[PLAYER_SOLDIER3_ID].attack = SOLDIER_ATTACK;
	gamePieces[PLAYER_SOLDIER3_ID].defense = SOLDIER_DEFENSE;
	gamePieces[PLAYER_SOLDIER3_ID].movPow = SOLDIER_MOVPOWER;
	gamePieces[PLAYER_SOLDIER3_ID].status = ALIVE_MASK;

	pieceMap[10][14] = PLAYER_SOLDIER4_ID;
	gamePieces[PLAYER_SOLDIER4_ID].x = 10;
	gamePieces[PLAYER_SOLDIER4_ID].y = 14;
	gamePieces[PLAYER_SOLDIER4_ID].hitPoint = SOLDIER_HITPOINT;
	gamePieces[PLAYER_SOLDIER4_ID].pieceType = PIECE_SOLDIER;
	gamePieces[PLAYER_SOLDIER4_ID].attack = SOLDIER_ATTACK;
	gamePieces[PLAYER_SOLDIER4_ID].defense = SOLDIER_DEFENSE;
	gamePieces[PLAYER_SOLDIER4_ID].movPow = SOLDIER_MOVPOWER;
	gamePieces[PLAYER_SOLDIER4_ID].status = ALIVE_MASK;

	pieceMap[7][15] = PLAYER_ARCHER1_ID;
	gamePieces[PLAYER_ARCHER1_ID].x = 7;
	gamePieces[PLAYER_ARCHER1_ID].y = 15;
	gamePieces[PLAYER_ARCHER1_ID].hitPoint = ARCHER_HITPOINT;
	gamePieces[PLAYER_ARCHER1_ID].pieceType = PIECE_ARCHER;
	gamePieces[PLAYER_ARCHER1_ID].attack = ARCHER_ATTACK;
	gamePieces[PLAYER_ARCHER1_ID].defense = ARCHER_DEFENSE;
	gamePieces[PLAYER_ARCHER1_ID].movPow = ARCHER_MOVPOWER;
	gamePieces[PLAYER_ARCHER1_ID].status = ALIVE_MASK;

	pieceMap[9][15] = PLAYER_ARCHER2_ID;
	gamePieces[PLAYER_ARCHER2_ID].x = 9;
	gamePieces[PLAYER_ARCHER2_ID].y = 15;
	gamePieces[PLAYER_ARCHER2_ID].hitPoint = ARCHER_HITPOINT;
	gamePieces[PLAYER_ARCHER2_ID].pieceType = PIECE_ARCHER;
	gamePieces[PLAYER_ARCHER2_ID].attack = ARCHER_ATTACK;
	gamePieces[PLAYER_ARCHER2_ID].defense = ARCHER_DEFENSE;
	gamePieces[PLAYER_ARCHER2_ID].movPow = ARCHER_MOVPOWER;
	gamePieces[PLAYER_ARCHER2_ID].status = ALIVE_MASK;

}

//�@�n�}�̕\��
void showMapWithPieces()
{

	int x, y;

	printf("   1 2 3 4 5 6 7 8 9 A B C D E F\n");
	for (y = 1; y < MAP_WIDTH - 1; y++)
	{

		if (y < 10)
			printf(" %d", y);
		else
			printf(" %c", 'A' + (y - 10));

		for (x = 1; x < MAP_LENGTH - 1; x++)
		{
			if (terrainMap[x][y] == SQ_BLOCK)
				showSquareInfo(x, y, COLOR_BLOCK);	// �ړ��s�\�̃}�X
			else if (terrainMap[x][y] == SQ_GRASS)
				showSquareInfo(x, y, COLOR_GRASS);	// ���n�̃}�X
			else if (terrainMap[x][y] == SQ_SAND)
				showSquareInfo(x, y, COLOR_SAND);		// ���n�̃}�X
			else if (terrainMap[x][y] == SQ_ROCK)
				showSquareInfo(x, y, COLOR_ROCK);		// ���̃}�X
			else
				printf("  ");
		}

		printf("\n");
	}
}


//�@�n�}�̕\���A�\�Ȉړ��͈͂�\��
void showMoveRange()
{

	int x, y;

	printf("   1 2 3 4 5 6 7 8 9 A B C D E F\n");
	for (y = 1; y < MAP_WIDTH - 1; y++)
	{

		if (y < 10)
			printf(" %d", y);
		else
			printf(" %c", 'A' + (y - 10));

		for (x = 1; x < MAP_LENGTH - 1; x++)
		{
			if (moveRange[x][y] > 0 && moveRange[x][y] < 99)
				showSquareInfo(x, y, COLOR_RANGE);
			else if (terrainMap[x][y] == SQ_BLOCK)
				showSquareInfo(x, y, COLOR_BLOCK);
			else if (terrainMap[x][y] == SQ_GRASS)
				showSquareInfo(x, y, COLOR_GRASS);
			else if (terrainMap[x][y] == SQ_SAND)
				showSquareInfo(x, y, COLOR_SAND);
			else if (terrainMap[x][y] == SQ_ROCK)
				showSquareInfo(x, y, COLOR_ROCK);
			else
				printf("  ");
		}

		printf("\n");
	}
}


//�@�}�X�̕\��
void showSquareInfo(int x, int y, int color)
{
	HANDLE  hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);		// �}�X�̐F�̃n���h��

	SetConsoleTextAttribute(hConsole, COLOR_RESET);	// �}�X�̐F������

	if (pieceMap[x][y] == 0) // �󂫃}�X
	{
		SetConsoleTextAttribute(hConsole, color);		// �}�X�̕����̐F�͍��A�w�i�̐F��color
		printf("  ");		// �󂫃}�X�̂ŕ������Ȃ�
	}
	else
	{
		if (gamePieces[pieceMap[x][y]].status & ALIVE_MASK)
		{
			// ���̃}�X�ɐ����Ă�������̂ŕ\��
			switch (gamePieces[pieceMap[x][y]].pieceType)
			{
			case PIECE_CASTLE:
				if (gamePieces[pieceMap[x][y]].status & MOVED_MASK)
				{
					// ����������̂ŐF�͕�
					SetConsoleTextAttribute(hConsole, MOVED_COLOR + color);	// �}�X�̕����̐F��MOVED_COLOR�A�w�i�̐F��color
					if (gamePieces[pieceMap[x][y]].status & COM_PIECE_MASK)
						printf(" c");		// COM�̋�͏�����
					else
						printf(" C");		// �v���C���[�̋�͑啶��
				}
				else
				{
					SetConsoleTextAttribute(hConsole, color);		// �}�X�̕����̐F�͍��A�w�i�̐F��color
					if (gamePieces[pieceMap[x][y]].status & COM_PIECE_MASK)
						printf(" c");		// COM�̋�͏�����
					else
						printf(" C");		// �v���C���[�̋�͑啶��
				}
				break;
			case PIECE_ARCHER:
				if (gamePieces[pieceMap[x][y]].status & MOVED_MASK)
				{
					// ����������̂ŐF�͕�
					SetConsoleTextAttribute(hConsole, MOVED_COLOR + color);	// �}�X�̕����̐F��MOVED_COLOR�A�w�i�̐F��color
					if (gamePieces[pieceMap[x][y]].status & COM_PIECE_MASK)
						printf(" a");		// COM�̋�͏�����
					else
						printf(" A");		// �v���C���[�̋�͑啶��
				}
				else
				{
					SetConsoleTextAttribute(hConsole, color);		// �}�X�̕����̐F�͍��A�w�i�̐F��color
					if (gamePieces[pieceMap[x][y]].status & COM_PIECE_MASK)
						printf(" a");		// COM�̋�͏�����
					else
						printf(" A");		// �v���C���[�̋�͑啶��
				}
				break;
			case PIECE_SOLDIER:
				if (gamePieces[pieceMap[x][y]].status & MOVED_MASK)
				{
					// ����������̂ŐF�͕�
					SetConsoleTextAttribute(hConsole, MOVED_COLOR + color);	// �}�X�̕����̐F��MOVED_COLOR�A�w�i�̐F��color
					if (gamePieces[pieceMap[x][y]].status & COM_PIECE_MASK)
						printf(" s");		// COM�̋�͏�����
					else
						printf(" S");		// �v���C���[�̋�͑啶��
				}
				else
				{
					SetConsoleTextAttribute(hConsole, color);		// �}�X�̕����̐F�͍��A�w�i�̐F��color
					if (gamePieces[pieceMap[x][y]].status & COM_PIECE_MASK)
						printf(" s");		// COM�̋�͏�����
					else
						printf(" S");		// �v���C���[�̋�͑啶��
				}
				break;
			case PIECE_KNIGHT:
				if (gamePieces[pieceMap[x][y]].status & MOVED_MASK)
				{
					// ����������̂ŐF�͕�
					SetConsoleTextAttribute(hConsole, MOVED_COLOR + color);	// �}�X�̕����̐F��MOVED_COLOR�A�w�i�̐F��color
					if (gamePieces[pieceMap[x][y]].status & COM_PIECE_MASK)
						printf(" k");		// COM�̋�͏�����
					else
						printf(" K");		// �v���C���[�̋�͑啶��
				}
				else
				{
					SetConsoleTextAttribute(hConsole, color);		// �}�X�̕����̐F�͍��A�w�i�̐F��color
					if (gamePieces[pieceMap[x][y]].status & COM_PIECE_MASK)
						printf(" k");		// COM�̋�͏�����
					else
						printf(" K");		// �v���C���[�̋�͑啶��
				}
				break;
			default:
				printf("  ");
				break;
			}
		}
	}
	SetConsoleTextAttribute(hConsole, COLOR_RESET);	// �}�X�̐F������
}

// ���ׂĂ̋�̏���\��
void showPieceStatus()
{
	char x, y;

	for (int pieceId = 1; pieceId <= TOTAL_PIECE_NUMBER; pieceId++)
	{
		if (gamePieces[pieceId].status & ALIVE_MASK)
		{

			if (gamePieces[pieceId].x < 10)
				x = '0' + gamePieces[pieceId].x;
			else
				x = 'A' + (gamePieces[pieceId].x - 10);

			if (gamePieces[pieceId].y < 10)
				y = '0' + gamePieces[pieceId].y;
			else
				y = 'A' + (gamePieces[pieceId].y - 10);

			if (gamePieces[pieceId].status & COM_PIECE_MASK)
			{
				switch (gamePieces[pieceId].pieceType)
				{
				case PIECE_CASTLE:
					printf(" c %c%c HP:%d, At:%d, Df:%d, Mp:%d\n",
						x, y, gamePieces[pieceId].hitPoint,
						gamePieces[pieceId].attack, gamePieces[pieceId].defense, gamePieces[pieceId].movPow);
					break;
				case PIECE_ARCHER:
					printf(" a %c%c HP:%d, At:%d, Df:%d, Mp:%d\n",
						x, y, gamePieces[pieceId].hitPoint,
						gamePieces[pieceId].attack, gamePieces[pieceId].defense, gamePieces[pieceId].movPow);
					break;
				case PIECE_KNIGHT:
					printf(" k %c%c HP:%d, At:%d, Df:%d, Mp:%d\n",
						x, y, gamePieces[pieceId].hitPoint,
						gamePieces[pieceId].attack, gamePieces[pieceId].defense, gamePieces[pieceId].movPow);
					break;
				case PIECE_SOLDIER:
					printf(" s %c%c HP:%d, At:%d, Df:%d, Mp:%d\n",
						x, y, gamePieces[pieceId].hitPoint,
						gamePieces[pieceId].attack, gamePieces[pieceId].defense, gamePieces[pieceId].movPow);
					break;
				default:
					break;
				}
			}
			else
			{
				switch (gamePieces[pieceId].pieceType)
				{
				case PIECE_CASTLE:
					printf(" C %c%c HP:%d, At:%d, Df:%d, Mp:%d\n",
						x, y, gamePieces[pieceId].hitPoint,
						gamePieces[pieceId].attack, gamePieces[pieceId].defense, gamePieces[pieceId].movPow);
					break;
				case PIECE_ARCHER:
					printf(" A %c%c HP:%d, At:%d, Df:%d, Mp:%d\n",
						x, y, gamePieces[pieceId].hitPoint,
						gamePieces[pieceId].attack, gamePieces[pieceId].defense, gamePieces[pieceId].movPow);
					break;
				case PIECE_KNIGHT:
					printf(" K %c%c HP:%d, At:%d, Df:%d, Mp:%d\n",
						x, y, gamePieces[pieceId].hitPoint,
						gamePieces[pieceId].attack, gamePieces[pieceId].defense, gamePieces[pieceId].movPow);
					break;
				case PIECE_SOLDIER:
					printf(" S %c%c HP:%d, At:%d, Df:%d, Mp:%d\n",
						x, y, gamePieces[pieceId].hitPoint,
						gamePieces[pieceId].attack, gamePieces[pieceId].defense, gamePieces[pieceId].movPow);
					break;
				default:
					break;
				}
			}
		}
	}

}

// ���W��\��
void displayCoordinates(int x, int y)
{
	char cx, cy;

	if (x < 10)
		cx = '0' + x;
	else
		cx = 'A' + (x - 10);

	if (y < 10)
		cy = '0' + y;
	else
		cy = 'A' + (y - 10);

	printf("%c%c", cx, cy);
}

// �v���C���[�̋�ړ�����
void selectAndMovePlayerPiece()
{

	int x, y, dx, dy, pieceId;

	getPlayerPiece(&x, &y);		// �v���C���[��������������̏ꏊ���l��

	pieceId = pieceMap[x][y];

	if (gamePieces[pieceId].status & MOVED_MASK)
	{
		printf("You already moved this piece.\n");	//	���ɓ�������
	}
	else
	{
		// ���̋�̈ړ��͈͂��v�Z�ƕ\��
		fillMap(moveRange, 0);
		findMoveRange(x, y, &gamePieces[pieceId], PLAYER);
		showMoveRange();

		getPlayerDestination(pieceId, &dx, &dy);		// �v���C���[����ړ���̏ꏊ���l��

		// ��̈ړ��֌W�����X�V
		pieceMap[dx][dy] = pieceMap[x][y];
		gamePieces[pieceId].x = dx;
		gamePieces[pieceId].y = dy;
		gamePieces[pieceId].status = gamePieces[pieceId].status | MOVED_MASK;
		if (x != dx || y != dy)
			pieceMap[x][y] = 0;
		resolveBattle(&gamePieces[pieceId], PLAYER);	// �키�����I�����Ă���o�g��

		if (gameStatus != PLAYER_WINS) // �o�g���̌��ʂŃQ�[���I�[�o�[�ɂȂ��ĂȂ��ꍇ
		{
			piecesToMove--;
			if (piecesToMove == 0)
			{
				nextToCastleRecovery(COMPUTER);		// ��ׂ̗̋����

				// �v���C���[�͂��ׂĂ̋�𓮂������̂�COM�̎�ԂɈڂ�
				gameStatus = COM_TO_MOVE;
				piecesToMove = comAlivePieceNo;

				// COM�̋���u�����Ă��Ȃ��v�󋵂ɐݒ�
				for (pieceId = 1; pieceId <= TOTAL_PIECE_NUMBER; pieceId++)
				{
					if (gamePieces[pieceId].status & COM_PIECE_MASK)
						gamePieces[pieceId].status &= ~MOVED_MASK;
				}

			}

		}
	}
}

// �v���C���[��������������̏ꏊ���m��
void getPlayerPiece(int *x, int *y)
{

	int tempX, tempY, legalX, legalY, legalPiece;
	int i;
	char c;
	char buf[256];

	legalX = legalY = legalPiece = 0;
	tempX = tempY = 0;
	// ����������l���ł���܂Ń��[�U�ɏ���v��
	while (!legalPiece)
	{
		// ������x�܂ŌJ��Ԃ�
		while (!legalX)
		{
			printf("Enter x coordinate of piece (1-F): ");
			c = getchar();
			for (i = 0; c != '\n'; i++)
			{
				buf[i] = c;
				c = getchar();
			}
			buf[i] = '\0';
			if (buf[0] >= '1' && buf[0] <= '9')
			{
				tempX = (buf[0] - '1') + 1;
				legalX = 1;
			}
			else if (buf[0] >= 'A' && buf[0] <= 'F')
			{
				tempX = (buf[0] - 'A') + 10;
				legalX = 1;
			}
			else
			{
				printf("The x-coordinate should be between 1 and F.\n");
				tempX = 0;
			}
		}
		// ������y�܂ŌJ��Ԃ�
		while (!legalY)
		{
			printf("Enter y coordinate of piece (1-F): ");
			c = getchar();
			for (i = 0; c != '\n'; i++)
			{
				buf[i] = c;
				c = getchar();
			}
			buf[i] = '\0';
			if (buf[0] >= '1' && buf[0] <= '9')
			{
				tempY = (buf[0] - '1') + 1;
				legalY = 1;
			}
			else if (buf[0] >= 'A' && buf[0] <= 'F')
			{
				tempY = (buf[0] - 'A') + 10;
				legalY = 1;
			}
			else
			{
				printf("The y-coordinate should be between 1 and F.\n");
				tempY = 0;
			}
		}
		if (pieceMap[tempX][tempY] == 0)
		{
			// �I�񂾃}�X�ɋ�Ȃ�
			printf("No piece on this square. Please try again.\n");
			legalX = 0;
			legalY = 0;
			tempX = 0;
			tempY = 0;
		}
		else if (gamePieces[pieceMap[tempX][tempY]].pieceType == PIECE_CASTLE)
		{
			// ��͓����Ȃ�
			printf("Cannot move castle. Please try again.\n");
			legalX = 0;
			legalY = 0;
			tempX = 0;
			tempY = 0;
		}
		else if (gamePieces[pieceMap[tempX][tempY]].status & COM_PIECE_MASK)
		{
			// COM�̋�͑I�ׂȂ�
			printf("This is not your piece. Please try again.\n");
			legalX = 0;
			legalY = 0;
			tempX = 0;
			tempY = 0;
		}
		else if (gamePieces[pieceMap[tempX][tempY]].status & MOVED_MASK)
		{
			// ���ɓ�������͑I�ׂȂ�
			printf("You already moved this piece. Please try again.\n");
			legalX = 0;
			legalY = 0;
			tempX = 0;
			tempY = 0;
		}
		else
		{
			// ��������
			legalPiece = 1;
			*x = tempX;
			*y = tempY;
		}
	}

}

// ��̈ړ�����m��
void getPlayerDestination(int pieceId, int *x, int *y)
{

	int tempX, tempY, legalX, legalY, legalMove;
	int i;
	char c;
	char buf[256];

	legalX = legalY = legalMove = 0;
	tempX = tempY = 0;

	// �������ړ���܂ŌJ��Ԃ�
	while (!legalMove)
	{
		// ������x�܂ŌJ��Ԃ�
		while (!legalX)
		{
			printf("Enter x coordinate of destination square (1-F): ");
			c = getchar();
			for (i = 0; c != '\n'; i++)
			{
				buf[i] = c;
				c = getchar();
			}
			buf[i] = '\0';
			if (buf[0] >= '1' && buf[0] <= '9')
			{
				tempX = (buf[0] - '1') + 1;
				legalX = 1;
			}
			else if (buf[0] >= 'A' && buf[0] <= 'F')
			{
				tempX = (buf[0] - 'A') + 10;
				legalX = 1;
			}
			else
			{
				printf("The x-coordinate should be between 1 and F.\n");
				tempX = 0;
			}
		}
		// ������y�܂ŌJ��Ԃ�
		while (!legalY)
		{
			printf("Enter y coordinate of destination square (1-F): ");
			c = getchar();
			for (i = 0; c != '\n'; i++)
			{
				buf[i] = c;
				c = getchar();
			}
			buf[i] = '\0';
			if (buf[0] >= '1' && buf[0] <= '9')
			{
				tempY = (buf[0] - '1') + 1;
				legalY = 1;
			}
			else if (buf[0] >= 'A' && buf[0] <= 'F')
			{
				tempY = (buf[0] - 'A') + 10;
				legalY = 1;
			}
			else
			{
				printf("The y-coordinate should be between 1 and F.\n");
				tempY = 0;
			}
		}
		if (moveRange[tempX][tempY] == 0)
		{
			// �I�񂾈ړ���͈ړ��͈͊O
			printf("Cannot move piece to this square.\n");
			legalX = 0;
			legalY = 0;
			tempX = 0;
			tempY = 0;
		}
		else if (pieceMap[tempX][tempY] != 0 && pieceMap[tempX][tempY] != pieceId)
		{
			// �I�񂾈ړ���ɋ����
			printf("There is already a piece on this square.\n");
			legalX = 0;
			legalY = 0;
			tempX = 0;
			tempY = 0;
		}
		else
		{
			// �������ړ���
			legalMove = 1;
			*x = tempX;
			*y = tempY;
		}
	}
}

// ��Ԃ��t����
int flip(int to_move)
{
	if (to_move == PLAYER)
		return COMPUTER;
	else
		return PLAYER;
}

// ��̍ō�HP��Ԃ��֐�
int getFullHitPointsForPiece(int piece)
{
	switch (piece)
	{
	case PIECE_CASTLE: return CASTLE_HITPOINT;
	case PIECE_KNIGHT: return KNIGHT_HITPOINT;
	case PIECE_SOLDIER: return SOLDIER_HITPOINT;
	case PIECE_ARCHER: return ARCHER_HITPOINT;
	default: return 0;
	}
}

// �邩��l�����̑�����͏邩��HP������āA�񕜂���
void nextToCastleRecovery(int side)
{
	int castleId, castleX, castleY, tempId, oldHp;

	if (side == COMPUTER)
		castleId = COM_CASTLE_ID;
	else
		castleId = PLAYER_CASTLE_ID;

	// ���HP��WEAK_CASTLE�������Ă�����񕜂��Ȃ�
	if (gamePieces[castleId].hitPoint > WEAK_CASTLE)
	{

		castleX = gamePieces[castleId].x;
		castleY = gamePieces[castleId].y;

		// ����񕜂����Ă݂āA���Ƃ�HP�ƕω����Ă��Ȃ�������i�񕜍ς݂�������j���HP�͌��炳�Ȃ�
		if (castleX > 1)
		{
			tempId = pieceMap[castleX - 1][castleY];
			if (tempId != 0 && (gamePieces[tempId].status & ALIVE_MASK) &&
				((side == COMPUTER && (gamePieces[tempId].status & COM_PIECE_MASK)) ||
				(side == PLAYER && !(gamePieces[tempId].status & COM_PIECE_MASK))))
			{
				oldHp = gamePieces[tempId].hitPoint;
				gamePieces[tempId].hitPoint = getFullHitPointsForPiece(gamePieces[tempId].pieceType);
				if (oldHp < gamePieces[tempId].hitPoint)
				{
					gamePieces[castleId].hitPoint -= (gamePieces[tempId].hitPoint - oldHp) / RECOVERY_RATE + 1;
					printf("Piece on ");
					displayCoordinates(castleX - 1, castleY);
					printf(" has recovered health. New castle HP: %d\n", gamePieces[castleId].hitPoint);
				}
			}
		}

		if (castleX < MAP_WIDTH - 2)
		{
			tempId = pieceMap[castleX + 1][castleY];
			if (tempId != 0 && (gamePieces[tempId].status & ALIVE_MASK) &&
				((side == COMPUTER && (gamePieces[tempId].status & COM_PIECE_MASK)) ||
				(side == PLAYER && !(gamePieces[tempId].status & COM_PIECE_MASK))))
			{
				oldHp = gamePieces[tempId].hitPoint;
				gamePieces[tempId].hitPoint = getFullHitPointsForPiece(gamePieces[tempId].pieceType);
				if (oldHp < gamePieces[tempId].hitPoint)
				{
					gamePieces[castleId].hitPoint -= (gamePieces[tempId].hitPoint - oldHp) / RECOVERY_RATE + 1;
					printf("Piece on ");
					displayCoordinates(castleX + 1, castleY);
					printf(" has recovered health. New castle HP: %d\n", gamePieces[castleId].hitPoint);
				}
			}
		}

		if (castleY > 1)
		{
			tempId = pieceMap[castleX][castleY - 1];
			if (tempId != 0 && (gamePieces[tempId].status & ALIVE_MASK) &&
				((side == COMPUTER && (gamePieces[tempId].status & COM_PIECE_MASK)) ||
				(side == PLAYER && !(gamePieces[tempId].status & COM_PIECE_MASK))))
			{
				oldHp = gamePieces[tempId].hitPoint;
				gamePieces[tempId].hitPoint = getFullHitPointsForPiece(gamePieces[tempId].pieceType);
				if (oldHp < gamePieces[tempId].hitPoint)
				{
					gamePieces[castleId].hitPoint -= (gamePieces[tempId].hitPoint - oldHp) / RECOVERY_RATE + 1;
					printf("Piece on ");
					displayCoordinates(castleX, castleY - 1);
					printf(" has recovered health. New castle HP: %d\n", gamePieces[castleId].hitPoint);
				}
			}
		}

		if (castleY < MAP_LENGTH - 2)
		{
			tempId = pieceMap[castleX][castleY + 1];
			if (tempId != 0 && (gamePieces[tempId].status & ALIVE_MASK) &&
				((side == COMPUTER && (gamePieces[tempId].status & COM_PIECE_MASK)) ||
				(side == PLAYER && !(gamePieces[tempId].status & COM_PIECE_MASK))))
			{
				oldHp = gamePieces[tempId].hitPoint;
				gamePieces[tempId].hitPoint = getFullHitPointsForPiece(gamePieces[tempId].pieceType);
				if (oldHp < gamePieces[tempId].hitPoint)
				{
					gamePieces[castleId].hitPoint -= (gamePieces[tempId].hitPoint - oldHp) / RECOVERY_RATE + 1;
					printf("Piece on ");
					displayCoordinates(castleX, castleY + 1);
					printf(" has recovered health. New castle HP: %d\n", gamePieces[castleId].hitPoint);
				}
			}
		}

	}

}

// �키�����I�����Ă���o�g���B������A����̋��S���j������Q�[���I�[�o�[
void resolveBattle(PIECE *piece, int side)
{
	int oppId;

	oppId = selectOpponent(piece, side);		// �키�����I��

	if (oppId != 0)
	{
		fightBattle(piece, oppId);				// �o�g��

		// ������A����̋��S���j������Q�[���I�[�o�[
		if (playerAlivePieceNo == 0 || playerCastleDestroyed)
			gameStatus = COM_WINS;
		else if (comAlivePieceNo == 0 || comCastleDestroyed)
			gameStatus = PLAYER_WINS;
	}

}

// �키�����I��
int selectOpponent(PIECE *piece, int side)
{
	int myX = piece->x;
	int myY = piece->y;
	int oppId[4];
	int oppNo = 0;
	int legalId;
	char c, buf[80];
	int i, tempId;

	if (side == PLAYER)
	{
		// ��Ԃ̓v���C���[�̂œG��I�����Ă��炤
		if (myX < MAP_WIDTH - 2)
		{
			// �E�ׂɓG���m�F
			oppId[oppNo] = pieceMap[myX + 1][myY];
			if (oppId[oppNo] && gamePieces[oppId[oppNo]].status & COM_PIECE_MASK)
			{
				// �G���̏���\��
				printf("Battle opponent %d at ", oppNo + 1);
				displayCoordinates(myX + 1, myY);
				printf(", MyHP: %d, OppHP: %d, Attack: %d, Defense: %d\n",
					piece->hitPoint, gamePieces[oppId[oppNo]].hitPoint, gamePieces[oppId[oppNo]].attack, gamePieces[oppId[oppNo]].defense);
				oppNo++;
			}
		}
		if (myX > 1)
		{
			// ���ׂɓG���m�F
			oppId[oppNo] = pieceMap[myX - 1][myY];
			if (oppId[oppNo] && gamePieces[oppId[oppNo]].status & COM_PIECE_MASK)
			{
				// �G���̏���\��
				printf("Battle opponent %d at ", oppNo + 1);
				displayCoordinates(myX - 1, myY);
				printf(", MyHP: %d, OppHP: %d, Attack: %d, Defense: %d\n",
					piece->hitPoint, gamePieces[oppId[oppNo]].hitPoint, gamePieces[oppId[oppNo]].attack, gamePieces[oppId[oppNo]].defense);
				oppNo++;
			}
		}
		if (myY < MAP_LENGTH - 2)
		{
			// ���ׂɓG���m�F
			oppId[oppNo] = pieceMap[myX][myY + 1];
			if (oppId[oppNo] && gamePieces[oppId[oppNo]].status & COM_PIECE_MASK)
			{
				// �G���̏���\��
				printf("Battle opponent %d at ", oppNo + 1);
				displayCoordinates(myX, myY + 1);
				printf(", MyHP: %d, OppHP: %d, Attack: %d, Defense: %d\n",
					piece->hitPoint, gamePieces[oppId[oppNo]].hitPoint, gamePieces[oppId[oppNo]].attack, gamePieces[oppId[oppNo]].defense);
				oppNo++;
			}
		}
		if (myY > 1)
		{
			// ���ׂɓG���m�F
			oppId[oppNo] = pieceMap[myX][myY - 1];
			if (oppId[oppNo] && gamePieces[oppId[oppNo]].status & COM_PIECE_MASK)
			{
				// �G���̏���\��
				printf("Battle opponent %d at ", oppNo + 1);
				displayCoordinates(myX, myY - 1);
				printf(", MyHP: %d, OppHP: %d, Attack: %d, Defense: %d\n",
					piece->hitPoint, gamePieces[oppId[oppNo]].hitPoint, gamePieces[oppId[oppNo]].attack, gamePieces[oppId[oppNo]].defense);
				oppNo++;
			}
		}
		if (oppNo != 0)
		{
			// �v���C���[�ɓG��I��ł��炤
			legalId = 0;
			while (!legalId)
			{
				printf("Select battle opponent number: ");
				c = getchar();
				for (i = 0; c != '\n'; i++)
				{
					buf[i] = c;
					c = getchar();
				}
				buf[i] = '\0';
				if (buf[0] >= '1' && buf[0] <= '9')
				{
					tempId = (buf[0] - '1') + 1;
					if (tempId <= oppNo)
						return oppId[tempId - 1];
					else
						printf("Incorrect battle opponent number, please try again\n");
				}
				else
					printf("Incorrect battle opponent number, please try again\n");
			}
		}
	}
	else
	{
		// ��Ԃ�COM�̂ł��̕�����AI�ɂȂ��Ƃ��낪���邪�A���݂͈�ԑ̗͂��Ⴂ�����G�ɂ���
		if (myX < MAP_WIDTH - 2)
		{
			// �E�ׂɓG���m�F
			oppId[oppNo] = pieceMap[myX + 1][myY];
			if (oppId[oppNo] && !(gamePieces[oppId[oppNo]].status & COM_PIECE_MASK))
				oppNo++;
		}
		if (myX > 1)
		{
			// ���ׂɓG���m�F
			oppId[oppNo] = pieceMap[myX - 1][myY];
			if (oppId[oppNo] && !(gamePieces[oppId[oppNo]].status & COM_PIECE_MASK))
				oppNo++;
		}
		if (myY < MAP_LENGTH - 2)
		{
			// ���ׂɓG���m�F
			oppId[oppNo] = pieceMap[myX][myY + 1];
			if (oppId[oppNo] && !(gamePieces[oppId[oppNo]].status & COM_PIECE_MASK))
				oppNo++;
		}
		if (myY > 1)
		{
			// ���ׂɓG���m�F
			oppId[oppNo] = pieceMap[myX][myY - 1];
			if (oppId[oppNo] && !(gamePieces[oppId[oppNo]].status & COM_PIECE_MASK))
				oppNo++;
		}
		if (oppNo != 0)
		{
			// �̗͂��Ⴂ�G��I��
			tempId = oppId[0];
			for (i = 1; i < oppNo; i++)
			{
				if (gamePieces[oppId[i]].hitPoint < gamePieces[tempId].hitPoint)
					tempId = oppId[i];
			}
			return tempId;

		}
	}

	return 0;
}

// �o�g��
void fightBattle(PIECE *piece, int oppId)
{
	printf("Starting battle between ");
	displayCoordinates(piece->x, piece->y);
	printf(" and ");
	displayCoordinates(gamePieces[oppId].x, gamePieces[oppId].y);
	printf("...\n");

	// �U�����̐搧�U��
	gamePieces[oppId].hitPoint -= updateBattleHitPoints(piece->attack, gamePieces[oppId].defense,
		pieceCompatibility[piece->pieceType][gamePieces[oppId].pieceType], groundPower[terrainMap[gamePieces[oppId].x][gamePieces[oppId].y]]);

	printf("Attacked piece hitpoints after attack: %d\n", gamePieces[oppId].hitPoint);

	if (gamePieces[oppId].hitPoint <= 0)
	{
		// �U�����ꂽ�����
		printf("Attacked piece died in battle\n");
		if (gamePieces[oppId].pieceType == PIECE_CASTLE)
		{
			if (gamePieces[oppId].status & COM_PIECE_MASK)
				comCastleDestroyed = 1;
			else
				playerCastleDestroyed = 1;
		}
		else
		{
			if (gamePieces[oppId].status & COM_PIECE_MASK)
				comAlivePieceNo--;
			else
				playerAlivePieceNo--;
		}
		pieceMap[gamePieces[oppId].x][gamePieces[oppId].y] = 0;
		gamePieces[oppId].status &= ~ALIVE_MASK;
	}
	else
	{
		//���ȂȂ������甽���i�����͍U���̔����j
		piece->hitPoint -= updateBattleHitPoints(gamePieces[oppId].attack / 2, piece->defense,
			pieceCompatibility[piece->pieceType][gamePieces[oppId].pieceType], groundPower[terrainMap[piece->x][piece->y]]);

		printf("Attacking piece hitpoints after counter attack: %d\n", piece->hitPoint);

		if (piece->hitPoint <= 0)
		{
			// �U����������񂾁i��͍U�����Ȃ��̂Ŋ֌W�Ȃ��j
			printf("Attacking piece died in battle\n");
			if (piece->status & COM_PIECE_MASK)
				comAlivePieceNo--;
			else
				playerAlivePieceNo--;
			pieceMap[piece->x][piece->y] = 0;
			piece->status &= ~ALIVE_MASK;
		}
	}
}

// �o�g���̂Ƃ���HP���X�V�v�Z
int updateBattleHitPoints(int attackerAtPow, int defenderDefPow, int attackerDefenderCmp, int defenderGroundPower)
{
	int	atPow, defPow;

	//�U���́E�h��͂̎Z�o
	attackerAtPow += ((rand() % 10) - 5);			//�΂������������
	atPow = attackerAtPow + (attackerAtPow * attackerDefenderCmp) / 100;	//���Ȃ̂�100�Ŋ���
	defPow = defenderDefPow + (defenderDefPow * defenderGroundPower) / 100;

	switch (rand() % 20)
	{
	case 0:		//�t�@���u��
		atPow /= 2;
		break;

	case 1:		//�N���e�B�J��
		atPow *= 2;
		break;
	}

	atPow += (atPow - defPow);
	if (atPow < 0){ atPow = 0; }						//�[���ȉ��Ȃ�O��

	return atPow;
}

//�@�^����ꂽ�ʒu����̈ړ��\�͈͂�g_range�z����Ɏ��߂�
void findMoveRange(int startX, int startY, const PIECE *aPiece, int turnSide)
{
	moveRange[startX][startY] = aPiece->movPow;

	excludePiece(flip(turnSide), 99);	// �G���̋���I�񂳂��邽�߁A�}�b�v�ړ��ő�l���l�ߍ���
	checkRange(startX, startY, aPiece->movPow, aPiece->pieceType, moveRange);
	excludePiece(flip(turnSide), 0);	// �G���̋�̈ʒu���ړ��\�͈͂��珜�O����

}

//�@�I��͈͂��������O����
void excludePiece(int turnSide, int fillInt)
{
	int	i0;

	for (i0 = 1; i0 <= TOTAL_PIECE_NUMBER; i0++)
	{
		if (((gamePieces[i0].status & COM_PIECE_MASK) == turnSide))
		{
			moveRange[gamePieces[i0].x][gamePieces[i0].y] = fillInt;
		}
	}
}

//�@�ċA�@�ňړ��\�͈͂��`�F�b�N����B�z��̓Y�����Ɗ֐��̈������t�ɂȂ��Ă��邱�Ƃɗv���ӁB
void checkRange(int startX, int startY, int leftPow, int pieceType, int aMap[][MAP_WIDTH])
{
	int	i0;

	aMap[startX][startY] = leftPow;	/*�c��ړ���*/

	i0 = leftPow - moveCost[pieceType][terrainMap[startX][startY - 1]];/*��*/
	if (aMap[startX][startY - 1] < i0)
	{
		checkRange(startX, startY - 1, i0, pieceType, aMap);
	}

	i0 = leftPow - moveCost[pieceType][terrainMap[startX][startY + 1]];/*��*/
	if (aMap[startX][startY + 1] < i0)
	{
		checkRange(startX, startY + 1, i0, pieceType, aMap);
	}

	i0 = leftPow - moveCost[pieceType][terrainMap[startX - 1][startY]];/*�E*/
	if (aMap[startX - 1][startY] < i0)
	{
		checkRange(startX - 1, startY, i0, pieceType, aMap);
	}

	i0 = leftPow - moveCost[pieceType][terrainMap[startX + 1][startY]];/*��*/
	if (aMap[startX + 1][startY] < i0)
	{
		checkRange(startX + 1, startY, i0, pieceType, aMap);
	}
}

//�@�ċA�@�ŖڕW�n�_����̏��v�����𒲂ׂĒn�}�z��Ɏ��߂�
void checkDistance(int startX, int startY, int cnsPow, int pieceType, int aMap[][MAP_WIDTH])
{
	int	i0;

	aMap[startX][startY] = cnsPow;	/*�����܂Ŕ�₵���ړ��R�X�g����������*/

	i0 = cnsPow + moveCost[pieceType][terrainMap[startX][startY - 1]];/*��*/
	if (aMap[startX][startY - 1] > i0)
	{
		checkDistance(startX, startY - 1, i0, pieceType, aMap);
	}

	i0 = cnsPow + moveCost[pieceType][terrainMap[startX][startY + 1]];/*��*/
	if (aMap[startX][startY + 1] > i0)
	{
		checkDistance(startX, startY + 1, i0, pieceType, aMap);
	}

	i0 = cnsPow + moveCost[pieceType][terrainMap[startX - 1][startY]];/*�E*/
	if (aMap[startX - 1][startY] > i0)
	{
		checkDistance(startX - 1, startY, i0, pieceType, aMap);
	}

	i0 = cnsPow + moveCost[pieceType][terrainMap[startX + 1][startY]];/*��*/
	if (aMap[startX + 1][startY] > i0)
	{
		checkDistance(startX + 1, startY, i0, pieceType, aMap);
	}
}

//�@�I��͈͍\���̂̏�����
void fillMap(int aMap[][MAP_WIDTH], int fillInt)
{
	int	i0, j0, k0 = 0;

	for (i0 = 1; i0 < MAP_LENGTH - 1; i0++)
	{
		for (j0 = 1; j0 < MAP_WIDTH - 1; j0++)
		{
			aMap[i0][j0] = fillInt;
		}
	}
}

// COM�̋�𓮂���
void moveComPieces()
{
	int pieceId, sx, sy, dx, dy;

	printf("Starting computer turn...\n");

	for (pieceId = 1; pieceId <= TOTAL_PIECE_NUMBER; pieceId++)
	{

		if (gamePieces[pieceId].status & COM_PIECE_MASK && gamePieces[pieceId].pieceType != PIECE_CASTLE &&
			gamePieces[pieceId].status & ALIVE_MASK)
		{
			// ���̋�̈ړ��͈͂��v�Z
			fillMap(moveRange, MIN_DISTANCE);
			sx = gamePieces[pieceId].x;
			sy = gamePieces[pieceId].y;
			findMoveRange(sx, sy, &gamePieces[pieceId], COMPUTER);

			decideComPieceDestination(pieceId, &dx, &dy);		// �������AI�̕����I

			// ��̈ړ��֌W�����X�V
			pieceMap[dx][dy] = pieceMap[sx][sy];
			gamePieces[pieceId].x = dx;
			gamePieces[pieceId].y = dy;
			gamePieces[pieceId].status = gamePieces[pieceId].status | MOVED_MASK;
			if (sx != dx || sy != dy)
				pieceMap[sx][sy] = 0;
			resolveBattle(&gamePieces[pieceId], COMPUTER);	// �키�����I�����Ă���o�g��
			if (gameStatus == COM_WINS)	// �o�g���̌��ʂŃQ�[���I�[�o�[�ɂȂ����ꍇ
				break;

			piecesToMove--;
			if (piecesToMove == 0)
				break;	// ���ׂĂ̋�𓮂�����
		}
	}

	if (gameStatus != COM_WINS)	// �o�g���̌��ʂŃQ�[���I�[�o�[�ɂȂ��Ă��Ȃ��ꍇ
	{
		printf("Computer turn finished. Your turn.\n");

		nextToCastleRecovery(PLAYER);		// ��ׂ̗̋����

		gameStatus = PLAYER_TO_MOVE;		// �v���C���[�̎��
		piecesToMove = playerAlivePieceNo;	// ��������̐�

		// �v���C���[�̋���u�����Ă��Ȃ��v�󋵂ɐݒ�
		for (pieceId = 1; pieceId <= TOTAL_PIECE_NUMBER; pieceId++)
		{
			if (!(gamePieces[pieceId].status & COM_PIECE_MASK))
				gamePieces[pieceId].status &= ~MOVED_MASK;
		}

	}

}

// COM�̋�̈ړ�������߂�
void decideComPieceDestination(int pieceId, int *dx, int *dy)
{
	// ���݂�AI�͏���U�ߗ��Ƃ��ړI
	cpuCastleDestroyer(pieceId, dx, dy);
}

//���ׂĂ̋�̓v���C���[�̏�Ɍ������āA�U�ߗ��Ƃ�
void cpuCastleDestroyer(int pieceId, int *resultX, int *resultY)
{
	int	advMap[MAP_WIDTH][MAP_LENGTH];			//�L���x�}�b�v
	int	i0, j0;										//�J�E���^�Ƃ�
	int castleNum;									//�G�̏��ID�A�^�[�Q�b�g�ɂȂ���ID
	int	tmpX, tmpY, tarX, tarY, minCost;

	//�G�̏�̔w�ԍ��𓾂�
	castleNum = PLAYER_CASTLE_ID;

	tarX = gamePieces[castleNum].x;
	tarY = gamePieces[castleNum].y;

	//�}�b�v�̏�����
	fillMap(tmpMap, MAX_DISTANCE);
	fillMap(moveRange, MIN_DISTANCE);

	//�e���|�������ő�����Ŗ��߂�B
	fillMap(advMap, MAX_DISTANCE);

	//�ړ��R�X�g�T�����z��͈̔͂���E���Ȃ��悤�ɁA�O����0�ɂ��Ă����B
	for (i0 = 0; i0 < MAP_WIDTH; i0++)
	{
		advMap[i0][0] = MIN_DISTANCE;
		advMap[i0][MAP_LENGTH - 1] = MIN_DISTANCE;
	}
	for (i0 = 0; i0 < MAP_LENGTH; i0++)
	{
		advMap[0][i0] = MIN_DISTANCE;
		advMap[MAP_WIDTH - 1][i0] = MIN_DISTANCE;
	}

	//�G�̏邩��̈ړ��R�X�g��L���x�}�b�v�ɏ�������
	checkDistance(tarX, tarY, MIN_DISTANCE, gamePieces[pieceId].pieceType, advMap);

	//��ōł��Ⴂ�R�X�g�̈ʒu�𒲂ׂ邩��A�O���͍ő�l�Ŗ��߂Ă���
	for (i0 = 0; i0 < MAP_WIDTH; i0++)
	{
		advMap[i0][0] = MAX_DISTANCE;
		advMap[i0][MAP_LENGTH - 1] = MAX_DISTANCE;
	}
	for (i0 = 0; i0 < MAP_LENGTH; i0++)
	{
		advMap[0][i0] = MAX_DISTANCE;
		advMap[MAP_WIDTH - 1][i0] = MAX_DISTANCE;
	}

	//�ړ��\�͈͂̒T��
	findMoveRange(gamePieces[pieceId].x, gamePieces[pieceId].y, &gamePieces[pieceId], COMPUTER);

	//��̂���ʒu�ɂ͈ړ��ł��Ȃ�
	for (i0 = 1; i0 <= TOTAL_PIECE_NUMBER; i0++)
	{
		if (gamePieces[i0].status & ALIVE_MASK)
		{
			tmpMap[gamePieces[i0].x][gamePieces[i0].y] = MIN_DISTANCE;
		}
	}

	//�ړ��ł��Ȃ��ʒu���玩�����g�̈ʒu�͏��O����i���͂��͂܂ꂽ�Ƃ��̖�������j
	tmpMap[gamePieces[pieceId].x][gamePieces[pieceId].y] = MAX_DISTANCE;

	//�Œ�R�X�g�ɍő�l�����Ă���
	minCost = MAX_DISTANCE;
	tmpX = -1;
	tmpY = -1;

	//�ړ��͈͂̒��ŗL���x���ł������_�i�L���x�}�b�v���̃X�R�A���ł��Ⴂ�_�j��T��
	for (i0 = 1; i0 < MAP_WIDTH - 1; i0++)
	{
		for (j0 = 1; j0 < MAP_LENGTH - 1; j0++)
		{
			if ((tmpMap[i0][j0] != MIN_DISTANCE) &&
				(moveRange[i0][j0] != MIN_DISTANCE) &&
				(minCost > advMap[i0][j0]))
			{
				minCost = advMap[i0][j0];
				tmpX = i0;
				tmpY = j0;
			}
		}
	}

	//���ʂ�Ԃ�
	*resultX = tmpX;
	*resultY = tmpY;
}
