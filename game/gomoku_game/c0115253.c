
//���ɓO���Ăق��������̂ŁAopen_three��closed_three�̕]���l���������邱�ƂŌ㔼�ł����Ă�悤�ɂ����B
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ���݂̍ŋ��̕]���l
const int bestEvalValues[] = { 40,60,60,35,5,20};
// �e�X�g�������]���lx
const int testValues[] = {40,60,60,35,5,25};

// �]���l�z��̒��A�]�������̏ꏊ
#define CLOSED_FOUR_VALUE	0		// 1�Ԗڂ̒l
#define OPEN_THREE_VALUE	1		// 2�Ԗڂ̒l
#define CLOSED_THREE_VALUE	2		// 3�Ԗڂ̒l
#define OPEN_TWO_VALUE		3		// 4�Ԗڂ̒l
#define CLOSED_TWO_VALUE	4		// 5�Ԗڂ̒l
#define INITIATIVE			5		// 6�Ԗڂ̒l

// �T���̍ő�[��
#define MAXDEPTH		3

// �}�X�̏��
#define EMPTY_SQUARE	0		// �󂫃}�X
#define BLACK_STONE		1		// ������
#define WHITE_STONE		2		// ������

//�@���
#define BLACK			1		// ���̎��
#define WHITE			2		// ���̎��

// �ܖڕ��ׂ̔Ղ̑傫����15
#define BOARDSIZE		15

// COM�Ɛl�Ԃ̓v���C���[
#define HUMAN				1		// �l��
#define BEST_AI				2		// ���݂̈�ԋ����ܖ�AI
#define TEST_AI				3		// �e�X�g������AI

char namesAI[][18] = { "", "", "BestAI", "TestAI" };

// �Q�[���̌���
#define UNFINISHED		0		// �܂��I����Ă��Ȃ�
#define BLACK_WIN		1		// ���̏���
#define WHITE_WIN		2		// ���̏���
#define DRAW			3		// ��������

// ���ʂȕ]���l
#define INFINITYVAL		32000	// ������
#define WINNING			30000	// ����

// �ő�̗����ł���l
#define MAXRANDBONUS	5

// ���ƌ���COM���l�Ԃ����Ǘ�����ϐ�
int blackPlayer;
int whitePlayer;

int gomokuBoard[BOARDSIZE + 1][BOARDSIZE + 1];  // �ܖڕ��ׂ̔�
int nextMoveX;										// ���̎��x��
int nextMoveY;										// ���̎��y��

int numberOfGames;			// ���ȑΐ�̏ꍇ�A�΋ǂ̐�

int rootToMove;		// �T���̏����ǖʂ̎��

int moveCount;		// �΋ǂ̌��݋ǖʂ܂Ŏw������̐�

					// �΋ǂ̎��ۑ����邽�߂̔z��
int gameRecord[(BOARDSIZE * BOARDSIZE) + 1][2];

// �f�[�^��ۑ����邽�߂̕ϐ�
int saveData;
FILE *dataFile;

//
// �Ղ̃}�X�̕]��
//
// �����ɋ߂��΂������]�����邽�߂̔z��D
// �����̌��ߕ��F�}�X����\�Ȍܖڕ��ׂ̐�
// �ߓx�͍Œ�3�A�[���痣�ꂽ�}�X�͍ő�8�̂ŕ]���̃{�[�i�X�l��0����5�܂ŁD
int potentialEvaluation[BOARDSIZE + 1][BOARDSIZE + 1] =
{
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 2, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 2, 2, 2, 2 },
	{ 0, 2, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 2, 2, 2, 2 },
	{ 0, 2, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 2, 2, 2, 2 },
	{ 0, 2, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 2, 2, 2, 2 },
	{ 0, 2, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 2, 2, 2, 2 },
	{ 0, 2, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 2, 2, 2, 2 },
	{ 0, 2, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 2, 2, 2, 2 },
	{ 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0 },
};

// �ǖʂɓ����F�̐΂̘A�����Ǘ����邽�߂̕΂�
int blackOpenFour;		// �����΂��l���т̐��A�u���b�N�Ȃ��F * B B B B *
int blackClosedFour;	// �����΂��l���т̐��A�����΂̃u���b�N (W B B B B *) ���Ղ̒[�Ƀu���b�N (E B B B B *)
int blackOpenThree;		// �����΂��O���т̐��A�u���b�N�Ȃ��F * B B B *
int blackClosedThree;	// �����΂��O���т̐��A�����΂̃u���b�N (W B B B *) ���Ղ̒[�Ƀu���b�N (E B B B *)
int blackOpenTwo;		// �����΂����т̐��A�u���b�N�Ȃ��F * B B *
int blackClosedTwo;		// �����΂����т̐��A�����΂̃u���b�N (W B B *) ���Ղ̒[�Ƀu���b�N (E B B *)
int whiteOpenFour;		// �����΂��l���т̐��A���Ɠ��l
int whiteClosedFour;	// �����΂��l���т̐��A���Ɠ��l
int whiteOpenThree;		// �����΂��O���т̐��A���Ɠ��l
int whiteClosedThree;	// �����΂��O���т̐��A���Ɠ��l
int whiteOpenTwo;		// �����΂����т̐��A���Ɠ��l
int whiteClosedTwo;		// �����΂����т̐��A���Ɠ��l

						// �֐��̃v���g�^�C�v
void makeBoardEmpty();
void showBoard();
void saveBoardToFile(FILE *);
int playGomokuGame();
int fiveInRowCheck(int, int, int);
int takeBackAfterGame(int);
int askForHumanInput(int);
void getNextHumanMove();
int getNumberOfGames();
int decideComputerMove(int);
int firstFreeSquareAI(int);
int randomFreeSquareAI(int);
int alphaBetaSearch(int, int, int, int);
int flip(int);
int evaluate(int, int, int);
void blackConnectionAdmin(int, int, int);
void whiteConnectionAdmin(int, int, int);

int main()
{
	char c, userSelection, i;
	int gameResult;
	int firstAI, secondAI;
	int firstAIWins, secondAIWins, drawNumber;
	int tempPlayer;
	char dataFileName[100];

	while (1)
	{
		// �����̏�����
		srand(time(NULL));

		// �Ƃ肠�����A�f�[�^�͕ۑ����Ȃ�
		saveData = 0;

		// �Ղ�������
		makeBoardEmpty();

		// �����ǖʂ�\��
		showBoard();

		// ���[�����j����\��
		printf("=============================================================\n");
		printf("This is a very weak Gomoku program made by Reijer Grimbergen.\n");
		printf("=============================================================\n");
		printf("Main menu:\n");
		printf("1) Play human against human\n");
		printf("2) Play with black against computer\n");
		printf("3) Play with white against computer\n");
		printf("4) Play computer against computer\n");
		printf("Q) Quit program\n");
		printf("Please enter your selection: ");

		c = getchar();
		userSelection = c;
		while ((c = getchar()) != '\n')
			;

		switch (userSelection)
		{
		case '1':
			// COM�͔��̏ꍇ�Ƀv���C���[��������
			blackPlayer = HUMAN;
			whitePlayer = HUMAN;
			// �Q�[�����ŏ�����Ō�܂ł��
			gameResult = playGomokuGame();
			// ���ʂ����[�U�̓`����
			if (gameResult == BLACK_WIN)
				printf("\nBlack player wins.\n\n");
			else if (gameResult == WHITE_WIN)
				printf("\nWhite player wins.\n\n");
			else if (gameResult == DRAW)
				printf("\nThis game ended in a draw.\n\n");
			else
				printf("\nGame was not finished.\n\n");

			printf("Press any key to continue.\n");
			while ((c = getchar()) != '\n')
				;
			break;

		case '2':
			// COM�͔��̏ꍇ�Ƀv���C���[��������
			whitePlayer = BEST_AI;
			// �Q�[�����ŏ�����Ō�܂ł��
			if (whitePlayer)
			{
				blackPlayer = HUMAN;
				gameResult = playGomokuGame();
				// ���ʂ����[�U�̓`����
				if (gameResult == BLACK_WIN)
					printf("\nBlack player wins.\n\n");
				else if (gameResult == WHITE_WIN)
					printf("\nWhite player wins.\n\n");
				else if (gameResult == DRAW)
					printf("\nThis game ended in a draw.\n\n");
				else
					printf("\nGame was not finished.\n\n");

				printf("Press any key to continue.\n");
				while ((c = getchar()) != '\n')
					;
			}
			break;

		case '3':
			// COM�͍��̏ꍇ�Ƀv���C���[��������
			blackPlayer = BEST_AI;
			if (blackPlayer)
			{
				whitePlayer = HUMAN;
				// �Q�[�����ŏ�����Ō�܂ł��
				gameResult = playGomokuGame();
				// ���ʂ����[�U�̓`����
				if (gameResult == BLACK_WIN)
					printf("\nBlack player wins.\n\n");
				else if (gameResult == WHITE_WIN)
					printf("\nWhite player wins.\n\n");
				else if (gameResult == DRAW)
					printf("\nThis game ended in a draw.\n\n");
				else
					printf("\nGame was not finished.\n\n");

				printf("Press any key to continue.\n");
				while ((c = getchar()) != '\n')
					;
			}
			break;

		case '4':
			// COMvsCOM
			blackPlayer = BEST_AI;
			whitePlayer = TEST_AI;

			// �Q�[�����ŏ�����Ō�܂ł��
			if (blackPlayer && whitePlayer)
			{

				firstAI = blackPlayer;
				secondAI = whitePlayer;

				numberOfGames = getNumberOfGames();

				// �f�[�^��ۑ����鏀��
				printf("Enter filename to save data: ");
				scanf("%s", dataFileName);
				scanf("%*c");
				dataFile = fopen(dataFileName, "w");
				if (dataFile == NULL)
					printf("Unable to open data file\n");
				else
					saveData = 1;

				firstAIWins = secondAIWins = drawNumber = 0;

				for (i = 1; i <= numberOfGames; i++)
				{
					printf("Starting game number %d\n", i);
					if (saveData)
						fprintf(dataFile, "Starting game number %d\n", i);

					gameResult = playGomokuGame();

					// ���ʂ�\��
					if (gameResult == BLACK_WIN)
					{
						printf("\nBlack player wins.\n");
						if (saveData)
							fprintf(dataFile, "\nBlack player wins.\n");
					}
					else if (gameResult == WHITE_WIN)
					{
						printf("\nWhite player wins.\n");
						if (saveData)
							fprintf(dataFile, "\nWhite player wins.\n");
					}
					else if (gameResult == DRAW)
					{
						printf("\nThis game ended in a draw.\n");
						if (saveData)
							fprintf(dataFile, "\nThis game ended in a draw.\n");
					}

					// �r�����ʂ��X�V
					if ((gameResult == BLACK_WIN && blackPlayer == firstAI) ||
						(gameResult == WHITE_WIN && whitePlayer == firstAI))
						firstAIWins++;
					else if ((gameResult == BLACK_WIN && blackPlayer == secondAI) ||
						(gameResult == WHITE_WIN && whitePlayer == secondAI))
						secondAIWins++;
					else if (gameResult == DRAW)
						drawNumber++;
					// ���Ɣ������ւ��āA���̑΋ǂ����
					if (i != numberOfGames)
					{
						printf("\nCurrent score: %s - %s %d-%d(%d)\n\n", namesAI[firstAI], namesAI[secondAI], firstAIWins, secondAIWins, drawNumber);
						if (saveData)
							fprintf(dataFile, "\nCurrent Score: %s - %s %d-%d(%d)\n\n", namesAI[firstAI], namesAI[secondAI], firstAIWins, secondAIWins, drawNumber);

						tempPlayer = blackPlayer;
						blackPlayer = whitePlayer;
						whitePlayer = tempPlayer;
						makeBoardEmpty();
						showBoard();
					}

				}

				// �ŏI���ʂ�\��
				printf("\nFinal result: %s - %s %d-%d(%d)\n\n", namesAI[firstAI], namesAI[secondAI], firstAIWins, secondAIWins, drawNumber);
				if (saveData) {
					fprintf(dataFile, "\nFinal result: %s - %s %d-%d(%d)\n\n", namesAI[firstAI], namesAI[secondAI], firstAIWins, secondAIWins, drawNumber);
					fclose(dataFile);
				}

				printf("Press any key to continue.\n");
				while ((c = getchar()) != '\n')
					;
			}
			break;

		case 'Q':
			return 0;

		default:
			printf("Illegal input: Please select one of the menu options.\n");
			break;
		}
	}
	return 0;
}

// �Ղ̏������F���ׂẴ}�X���󂫃}�X�ɂ���
void makeBoardEmpty()
{
	int x, y;

	for (x = 1; x <= BOARDSIZE; x++)
		for (y = 1; y <= BOARDSIZE; y++)
			gomokuBoard[x][y] = EMPTY_SQUARE;
}

// ���݂̋ǖʂ�\��
void showBoard()
{
	int x, y;

	printf("   �P �Q �R �S �T �U �V �W �X 10 11 12 13 14 15\n");
	for (y = 1; y <= BOARDSIZE; y++)
	{
		if (y < 10)
			printf(" %d", y);
		else
			printf("%d", y);
		for (x = 1; x <= BOARDSIZE; x++)
		{
			if (gomokuBoard[x][y] == BLACK_STONE)
				printf(" ��");
			else if (gomokuBoard[x][y] == WHITE_STONE)
				printf(" ��");
			else
				printf(" ��");
		}
		printf("\n");
	}
}

// ���݂̋ǖʂ��t�@�C���ɕۑ�
void saveBoardToFile(FILE *fp)
{
	int x, y;

	fprintf(fp, "   �P �Q �R �S �T �U �V �W �X 10 11 12 13 14 15\n");
	for (y = 1; y <= BOARDSIZE; y++)
	{
		if (y < 10)
			fprintf(fp, " %d", y);
		else
			fprintf(fp, "%d", y);
		for (x = 1; x <= BOARDSIZE; x++)
		{
			if (gomokuBoard[x][y] == BLACK_STONE)
				fprintf(fp, " ��");
			else if (gomokuBoard[x][y] == WHITE_STONE)
				fprintf(fp, " ��");
			else
				fprintf(fp, " ��");
		}
		fprintf(fp, "\n");
	}
}

// �΋ǂ̐������[�U�ɓ��͂��Ă��炤
int getNumberOfGames()
{
	int game_number = 1;

	printf("\nEnter number of games to play: ");
	scanf("%d", &game_number);
	scanf("%*c");

	return game_number;
}

// �l�ԑ�COM�̑΋ǁD�Q�[�����I���܂łɈȉ��̂��Ƃ��J��Ԃ��G
// 1) COM�̎�Ԃ�COM�̎�����߂�
// 2) �l�Ԃ̎�Ԃ̏ꍇ�ɐl�Ԃ̎���l��
int playGomokuGame()
{
	int gameResult = UNFINISHED;
	int toMove = BLACK;

	moveCount = 1;

	nextMoveX = 0;
	nextMoveY = 0;
	// �Q�[�����I���܂łɃv���C�𑱂�
	while (gameResult == UNFINISHED)
	{
		if ((toMove == BLACK && blackPlayer != HUMAN) ||
			(toMove == WHITE && whitePlayer != HUMAN))
		{
			// COM�̎��
			printf("Thinking about my move...\n");
			if (saveData)
				fprintf(dataFile, "Thinking about my move...\n");
			if (decideComputerMove(toMove))
			{
				printf("Computer move: %d) (%d,%d)\n", moveCount, nextMoveX, nextMoveY);
				if (saveData)
					fprintf(dataFile, "Computer move: %d) (%d,%d)\n", moveCount, nextMoveX, nextMoveY);
			}
			else //	COM�̎�͌��߂��Ȃ�
			{
				printf("Computer move could not be decided.\n");
				if (saveData)
					fprintf(dataFile, "Computer move could not be decided.\n");
				if (blackPlayer != HUMAN)
					gameResult = WHITE_WIN;
				else
					gameResult = BLACK_WIN;
				break;
			}
		}
		else
		{
			// �v���C���[�̎��
			if (askForHumanInput(toMove))
			{
				printf("You played: %d) (%d,%d)\n", moveCount, nextMoveX, nextMoveY);
				if (saveData)
					fprintf(dataFile, "You played: %d) (%d,%d)\n", moveCount, nextMoveX, nextMoveY);
			}
			else
			{
				printf("User aborted game.\n");
				break;
			}
		}

		// �΂�Ղɒu��
		if (toMove == BLACK)
			gomokuBoard[nextMoveX][nextMoveY] = BLACK_STONE;
		else
			gomokuBoard[nextMoveX][nextMoveY] = WHITE_STONE;

		// �X�V�����ǖʂ�\��
		showBoard();

		// �΋ǂ̎��ۑ�
		gameRecord[moveCount][0] = nextMoveX;
		gameRecord[moveCount][1] = nextMoveY;

		if (saveData)
			saveBoardToFile(dataFile);

		// �肪�����ꂽ�̂Ŏ萔���X�V
		moveCount++;

		// �I���������������Ă��邩�ǂ���
		if (fiveInRowCheck(nextMoveX, nextMoveY, toMove))
		{
			// �v���C���[�Ɏ��߂��`�����X������i�Ō�I�j
			if (!takeBackAfterGame(toMove))
			{
				if (toMove == BLACK)
					gameResult = BLACK_WIN;
				else
					gameResult = WHITE_WIN;
				break;
			}
		}
		// �Ղ������ς��ɂȂ������ǂ����̃`�F�b�N
		else if (moveCount == (BOARDSIZE * BOARDSIZE))
		{
			if (!takeBackAfterGame(toMove))
			{
				gameResult = DRAW;
				break;
			}
		}

		// ��Ԃ��X�V
		if (toMove == BLACK)
			toMove = WHITE;
		else
			toMove = BLACK;

		nextMoveX = 0;
		nextMoveY = 0;
	}

	return gameResult;
}

// �Ō�̎�̏��𗘗p���A�ܖڕ��ׂɂȂ������ǂ������`�F�b�N
int fiveInRowCheck(int lastX, int lastY, int color)
{
	int x, y;
	int connectNo = 1;

	// ���̌ܖڕ��׃`�F�b�N:(lastx, lasty)���W����color�Ɠ����F�̐΂̘A�����E�ƍ��ɂ��킹�Đ�����
	if (lastX > 1)
	{
		for (x = lastX - 1; gomokuBoard[x][lastY] == color; x--)
		{
			connectNo++;
			if (x == 1)
				break;
		}
	}
	if (lastX < BOARDSIZE)
	{
		for (x = lastX + 1; gomokuBoard[x][lastY] == color; x++)
		{
			connectNo++;
			if (x == BOARDSIZE)
				break;
		}
	}
	if (connectNo >= 5)
		return 1;			// ���̌ܖڕ��׌�����

							// �c�̌ܖڕ��׃`�F�b�N:(lastx, lasty)���W����color�Ɠ����F�̐΂̘A������Ɖ��ɂ��킹�Đ�����
	connectNo = 1;
	if (lastY > 1)
	{
		for (y = lastY - 1; gomokuBoard[lastX][y] == color; y--)
		{
			connectNo++;
			if (y == 1)
				break;
		}
	}
	if (lastY < BOARDSIZE)
	{
		for (y = lastY + 1; gomokuBoard[lastX][y] == color; y++)
		{
			connectNo++;
			if (y == BOARDSIZE)
				break;
		}
	}
	if (connectNo >= 5)
		return 1;			// �c�̌ܖڕ��׌�����

							// �΂߁i�k���|�쓌�j�̌ܖڕ��׃`�F�b�N:(lastx, lasty)���W����color�Ɠ����F�̐΂̘A����k���Ɠ쓌�ɂ��킹�Đ�����
	connectNo = 1;
	if (lastX > 1 && lastY > 1)
	{
		for (x = lastX - 1, y = lastY - 1; gomokuBoard[x][y] == color; x--, y--)
		{
			connectNo++;
			if (x == 1 || y == 1)
				break;
		}
	}
	if (lastX < BOARDSIZE && lastY < BOARDSIZE)
	{
		for (x = lastX + 1, y = lastY + 1; gomokuBoard[x][y] == color; x++, y++)
		{
			connectNo++;
			if (x == BOARDSIZE || y == BOARDSIZE)
				break;
		}
	}
	if (connectNo >= 5)
		return 1;			// �΂߁i�k���|�쓌�j�̌ܖڕ��׌�����

							// �΂߁i�k���|�쐼�j�̌ܖڕ��׃`�F�b�N:(lastx, lasty)���W����color�Ɠ����F�̐΂̘A����k���Ɠ쐼�ɂ��킹�Đ�����
	connectNo = 1;
	if (lastX < BOARDSIZE && lastY > 1)
	{
		for (x = lastX + 1, y = lastY - 1; gomokuBoard[x][y] == color; x++, y--)
		{
			connectNo++;
			if (x == BOARDSIZE || y == 1)
				break;
		}
	}
	if (lastX > 1 && lastY < BOARDSIZE)
	{
		for (x = lastX - 1, y = lastY + 1; gomokuBoard[x][y] == color; x--, y++)
		{
			connectNo++;
			if (x == 1 || y == BOARDSIZE)
				break;
		}
	}
	if (connectNo >= 5)
		return 1;			// �΂߁i�k���|�쐼�j�̌ܖڕ��׌�����

	return 0;
}

// �΋ǂ��I����Ă��܂������A���̓~�X���������̂Ŏ��߂����Ƃ��\����֐�
int takeBackAfterGame(int toMove)
{
	char c, userSelection;

	// ���߂��͐l�ԃv���C���[����
	if ((toMove == BLACK && blackPlayer == HUMAN) ||
		(toMove == WHITE && whitePlayer == HUMAN))
	{
		// �v���C���[�ɃI�v�V�����̑I����^����.�@���߂��������ǂ������m�F
		while (1)
		{
			printf("\nGame over. Do you want to take back moves? (y/n): ");

			c = getchar();
			userSelection = c;
			while ((c = getchar()) != '\n')
				;

			switch (userSelection)
			{
			case 'y':
				// �v���C���[�͎��߂������i�҂����@�\�j
				if (moveCount <= 2)
					printf("Cannot take back first move of the game.\n");
				else
				{
					moveCount--;
					gomokuBoard[gameRecord[moveCount][0]][gameRecord[moveCount][1]] = EMPTY_SQUARE;
					moveCount--;
					gomokuBoard[gameRecord[moveCount][0]][gameRecord[moveCount][1]] = EMPTY_SQUARE;
				}
				showBoard();
				return 1;

			case 'n':
				return 0;

			default:
				printf("Illegal input: Please select one of the menu options.\n");
				break;
			}
		}
	}

	return 0;
}

// �v���C���[�ɐV���������͂��邩�A�ȑO�w�������߂����ɕ���
int askForHumanInput(int toMove)
{

	char c, userSelection;

	// �v���C���[�ɃI�v�V�����̑I����^����D�������肪���͂��ꂽ���A�v���C���[�͂�߂邩�܂ł̃��[�v
	while (1)
	{
		// �I�����j��
		printf("1) Enter next move.\n");
		printf("2) Take back moves.\n");
		printf("Q) Quit game.\n");
		printf("Please enter your selection: ");

		c = getchar();
		userSelection = c;
		while ((c = getchar()) != '\n')
			;

		switch (userSelection)
		{
		case '1':
			// �v���C���[�͎��̎����͂�����
			getNextHumanMove();
			return 1;

		case '2':
			// �v���C���[�͎��߂������i�҂����@�\�j
			if (moveCount <= 2)
				printf("Cannot take back first move of the game.\n");
			else
			{
				moveCount--;
				gomokuBoard[gameRecord[moveCount][0]][gameRecord[moveCount][1]] = EMPTY_SQUARE;
				moveCount--;
				gomokuBoard[gameRecord[moveCount][0]][gameRecord[moveCount][1]] = EMPTY_SQUARE;
			}
			showBoard();
			break;

		case 'Q':
			return 0;

		default:
			printf("Illegal input: Please select one of the menu options.\n");
			break;
		}
	}

	return 0;
}

// �v���C���[����V�����Ă��l��
void getNextHumanMove()
{
	int legalX, legalY, legalMove;
	int i;
	char c;
	char buf[256];

	legalX = legalY = legalMove = 0;
	// ����������l���ł���܂łɌJ��Ԃ�
	while (!legalMove)
	{
		// ������x���̊l���܂ŌJ��Ԃ�
		while (!legalX)
		{
			printf("Enter x coordinate of move (1-15): ");
			c = getchar();
			for (i = 0; c != '\n'; i++)
			{
				buf[i] = c;
				c = getchar();
			}
			buf[i] = '\0';
			sscanf(buf, "%d", &nextMoveX);
			if (nextMoveX >= 1 && nextMoveX <= BOARDSIZE)
				legalX = 1;
			else
			{
				printf("The x-coordinate should be a number between 1 and 15.\n");
				nextMoveX = 0;
			}
		}
		// ������y���̊l���܂ŌJ��Ԃ�
		while (!legalY)
		{
			printf("Enter y coordinate of move (1-15): ");
			c = getchar();
			for (i = 0; c != '\n'; i++)
			{
				buf[i] = c;
				c = getchar();
			}
			buf[i] = '\0';
			sscanf(buf, "%d", &nextMoveY);
			if (nextMoveY >= 1 && nextMoveY <= BOARDSIZE)
				legalY = 1;
			else
			{
				printf("The y-coordinate should be a number between 1 and 15.\n");
				nextMoveY = 0;
			}
		}
		// �I�񂾃}�X�͋󂫃}�X���ǂ������m�F
		if (gomokuBoard[nextMoveX][nextMoveY] == EMPTY_SQUARE)
			legalMove = 1;
		else
		{
			printf("The selected square is not empty.\n");
			nextMoveX = 0;
			nextMoveY = 0;
			legalX = 0;
			legalY = 0;
		}
	}

}

// COM�̎�����߂�D����͌ܖڕ��׃v���O������AI�̕����D
int decideComputerMove(int toMove)
{
	int score;

	rootToMove = toMove;

	score = alphaBetaSearch(0, rootToMove, -INFINITYVAL, INFINITYVAL);
	printf("Best move evaluation: %d\n", score);
	if (saveData)
		fprintf(dataFile, "Best move evaluation: %d\n", score);

	return 1;
}

//
// Minmax�T����alpha-beta�}����
//
int alphaBetaSearch(int depth, int toMove, int alpha, int beta)
{
	int score, eval;
	int x, y;

	// �ő�[���ɂȂ�����ǖʂ�]������
	if (depth == MAXDEPTH)
		return evaluate(rootToMove, toMove, depth);

	// Max�v���C���[��Min�v���C���[�̍ō��]����������
	if (toMove == rootToMove)
		score = -INFINITYVAL;
	else
		score = INFINITYVAL;

	// Generate all the moves by putting stones of the right color on the empty squares
	// �󂢂Ă���}�X�ɐ������F�̐΂�u���āA���ׂĂ̎���쐬
	for (x = 1; x <= BOARDSIZE; x++)
	{
		for (y = 1; y <= BOARDSIZE; y++)
		{
			if (gomokuBoard[x][y] == EMPTY_SQUARE)
			{
				gomokuBoard[x][y] = toMove;
				// ���̎�Ōܖڕ��ׂɂȂ������ǂ������`�F�b�N
				if (fiveInRowCheck(x, y, toMove))
				{
					if (rootToMove == toMove)
					{
						// Max�v���C���[�̌ܖڕ���
						// ���߂�
						gomokuBoard[x][y] = EMPTY_SQUARE;
						// �����ɂȂ�����͒T���̏����ǖʂɂ������̂Ŏ��ۑ�����
						if (depth == 0)
						{
							nextMoveX = x;
							nextMoveY = y;
						}
						return WINNING - depth;			// �󂢒T���̏����͐[���T���̏������ǂ�
					}
					else
					{
						// Min�v���C���[�̌ܖڕ���
						// ���߂�
						gomokuBoard[x][y] = EMPTY_SQUARE;
						return -(WINNING - depth);	// �󂢒T���̏����͐[���T���̏������ǂ�
					}
				}
				else
				{
					// alpha-beta�T�����ċA�I�ɌĂ�
					eval = alphaBetaSearch(depth + 1, flip(toMove), alpha, beta);

					// ���߂�
					gomokuBoard[x][y] = EMPTY_SQUARE;

					if (rootToMove == toMove)
					{
						// ���̋ǖʂ�Max�v���C���[�̎�ԁD�T���̌��ʂ͌��݂̍ő�]����荂���Ȃ�΍ő�]�����X�V
						if (eval > score)
						{
							score = eval;
							// �őP��͒T���̏����ǖʂɂ������̂Ŏ��ۑ�����
							if (depth == 0)
							{
								nextMoveX = x;
								nextMoveY = y;
							}
						}

						// Beta�}����
						if (score >= beta)
							return score;
						// alpha���X�V
						if (score > alpha)
							alpha = score;
					}
					else
					{
						// ���̋ǖʂ�Min�v���C���[�̎�ԁD�T���̌��ʂ͌��݂̍Œ�]�����Ⴂ�Ȃ�΍Œ�]�����X�V
						if (eval < score)
							score = eval;

						// Alpha�}����
						if (score <= alpha)
							return score;
						// Beta���X�V
						if (beta < score)
							beta = score;
					}
				}
			}
		}
	}
	return score;
}

// ��Ԃ��t�ɂ���
int flip(int toMove)
{
	if (toMove == BLACK)
		return WHITE;
	else if (toMove == WHITE)
		return BLACK;
	return 0;
}

// ���݂̋ǖʂ�]��
// ���̒l�͍����΂̃p�^�[���ɑ΂��Ă̕]���Ȃ̂Ŕ��̕]���ł���Ε]���l�𐳕��t�ɂ���K�v������D
// �������f�̂��߂Ɍ��݂̋ǖʂ̎�ԁinextToMove�j���K�v�D
// �k�A�k���A���A�쐼�����̘A���m�F�͂��Ȃ��Ă悢�D�i�Ղ̒��ׂ�����ł��łɔ�������܂����j
// ���̕]���֐��͌������������A�l���������Ă��Ȃ��̂ŉ��P�]�n���\������D
int evaluate(int side, int nextToMove, int depth)
{
	int eval = 0;
	int x, y;
	int connectNo;			// �A���̓����F�̐΂̐�
	int emptySqCon;			// �A���͂ǂ��܂ŐL�΂���
	int blocked;			// �΂̘A���̓u���b�N����Ă���
	int countX, countY;

	blackOpenFour = 0;
	blackClosedFour = 0;
	blackOpenThree = 0;
	blackClosedThree = 0;
	blackOpenTwo = 0;
	blackClosedTwo = 0;
	whiteOpenFour = 0;
	whiteClosedFour = 0;
	whiteOpenThree = 0;
	whiteClosedThree = 0;
	whiteOpenTwo = 0;
	whiteClosedTwo = 0;

	for (x = 1; x <= BOARDSIZE; x++)
	{
		for (y = 1; y <= BOARDSIZE; y++)
		{

			if (gomokuBoard[x][y] == BLACK_STONE)
			{
				// ���̃}�X���獕���΂𐔂���

				// �k������
				connectNo = 1;
				emptySqCon = 0;

				// �΂̘A���͔Ղ̒[������̐΂Ƀu���b�N����Ă���
				if (x == 1 || y == BOARDSIZE || gomokuBoard[x - 1][y + 1] == WHITE_STONE)
					blocked = 1;
				else {
					blocked = 0;
					emptySqCon++;
				}

				// �΂̘A���𐔂���
				for (countX = x + 1, countY = y - 1; countX <= BOARDSIZE && countY >= 1; countX++, countY--)
				{
					if (gomokuBoard[countX][countY] == BLACK_STONE)
					{
						connectNo++;
					}
					else if (gomokuBoard[countX][countY] == WHITE_STONE)
					{
						blocked++;
						break;
					}
					else
					{
						break;
					}
				}
				// �ǂ��܂ŐL�΂��邩
				if (blocked <= 1 && connectNo > 1) {
					for (; countX <= BOARDSIZE && countY >= 1 && gomokuBoard[countX][countY] == EMPTY_SQUARE; countX++, countY--)
						emptySqCon++;
				}
				// �΂̘A���̎�ނ̐����X�V
				blackConnectionAdmin(connectNo, blocked, emptySqCon);

				// ������
				connectNo = 1;
				emptySqCon = 0;

				// �΂̘A���͔Ղ̒[������̐΂Ƀu���b�N����Ă���
				if (x == 1 || gomokuBoard[x - 1][y] == WHITE_STONE)
					blocked = 1;
				else {
					blocked = 0;
					emptySqCon++;
				}

				// �΂̘A���𐔂���
				countY = y;
				for (countX = x + 1; countX <= BOARDSIZE; countX++)
				{
					if (gomokuBoard[countX][countY] == BLACK_STONE)
					{
						connectNo++;
					}
					else if (gomokuBoard[countX][countY] == WHITE_STONE)
					{
						blocked++;
						break;
					}
					else
					{
						break;
					}
				}
				// �ǂ��܂ŐL�΂��邩
				if (blocked <= 1 && connectNo > 1) {
					for (; countX <= BOARDSIZE && gomokuBoard[countX][countY] == EMPTY_SQUARE; countX++)
						emptySqCon++;
				}
				// �΂̘A���̎�ނ̐����X�V
				blackConnectionAdmin(connectNo, blocked, emptySqCon);

				// �쓌����
				connectNo = 1;
				emptySqCon = 0;

				// �΂̘A���͔Ղ̒[������̐΂Ƀu���b�N����Ă���
				if (x == 1 || y == 1 || gomokuBoard[x - 1][y - 1] == WHITE_STONE)
					blocked = 1;
				else {
					blocked = 0;
					emptySqCon++;
				}

				// �΂̘A���𐔂���
				for (countX = x + 1, countY = y + 1; countX <= BOARDSIZE && countY <= BOARDSIZE; countX++, countY++)
				{
					if (gomokuBoard[countX][countY] == BLACK_STONE)
					{
						connectNo++;
					}
					else if (gomokuBoard[countX][countY] == WHITE_STONE)
					{
						blocked++;
						break;
					}
					else
					{
						break;
					}
				}
				// �ǂ��܂ŐL�΂��邩
				if (blocked <= 1 && connectNo > 1) {
					for (; countX <= BOARDSIZE && countY <= BOARDSIZE && gomokuBoard[countX][countY] == EMPTY_SQUARE; countX++, countY++)
						emptySqCon++;
				}
				// �΂̘A���̎�ނ̐����X�V
				blackConnectionAdmin(connectNo, blocked, emptySqCon);

				// �����
				connectNo = 1;
				emptySqCon = 0;

				// �΂̘A���͔Ղ̒[������̐΂Ƀu���b�N����Ă���
				if (y == 1 || gomokuBoard[x][y - 1] == WHITE_STONE)
					blocked = 1;
				else {
					blocked = 0;
					emptySqCon++;
				}

				// �΂̘A���𐔂���
				countX = x;
				for (countY = y + 1; countY <= BOARDSIZE; countY++)
				{
					if (gomokuBoard[countX][countY] == BLACK_STONE)
					{
						connectNo++;
					}
					else if (gomokuBoard[countX][countY] == WHITE_STONE)
					{
						blocked++;
						break;
					}
					else
					{
						break;
					}
				}
				// �ǂ��܂ŐL�΂��邩
				if (blocked <= 1 && connectNo > 1) {
					for (; countY <= BOARDSIZE && gomokuBoard[countX][countY] == EMPTY_SQUARE; countY++)
						emptySqCon++;
				}
				// �΂̘A���̎�ނ̐����X�V
				blackConnectionAdmin(connectNo, blocked, emptySqCon);

			}
			else if (gomokuBoard[x][y] == WHITE_STONE)
			{
				// ���̃}�X���獕���΂𐔂���

				// �k������
				connectNo = 1;
				emptySqCon = 0;

				// �΂̘A���͔Ղ̒[������̐΂Ƀu���b�N����Ă���
				if (x == 1 || y == BOARDSIZE || gomokuBoard[x - 1][y + 1] == BLACK_STONE)
					blocked = 1;
				else {
					blocked = 0;
					emptySqCon++;
				}

				// �΂̘A���𐔂���
				for (countX = x + 1, countY = y - 1; countX <= BOARDSIZE && countY >= 1; countX++, countY--)
				{
					if (gomokuBoard[countX][countY] == WHITE_STONE)
					{
						connectNo++;
					}
					else if (gomokuBoard[countX][countY] == BLACK_STONE)
					{
						blocked++;
						break;
					}
					else
					{
						break;
					}
				}
				// �ǂ��܂ŐL�΂��邩
				if (blocked <= 1 && connectNo > 1) {
					for (; countX <= BOARDSIZE && countY >= 1 && gomokuBoard[countX][countY] == EMPTY_SQUARE; countX++, countY--)
						emptySqCon++;
				}
				// �΂̘A���̎�ނ̐����X�V
				whiteConnectionAdmin(connectNo, blocked, emptySqCon);

				// ������
				connectNo = 1;
				emptySqCon = 0;

				// �΂̘A���͔Ղ̒[������̐΂Ƀu���b�N����Ă���
				if (x == 1 || gomokuBoard[x - 1][y] == BLACK_STONE)
					blocked = 1;
				else {
					blocked = 0;
					emptySqCon++;
				}

				// �΂̘A���𐔂���
				countY = y;
				for (countX = x + 1; countX <= BOARDSIZE; countX++)
				{
					if (gomokuBoard[countX][countY] == WHITE_STONE)
					{
						connectNo++;
					}
					else if (gomokuBoard[countX][countY] == BLACK_STONE)
					{
						blocked++;
						break;
					}
					else
					{
						break;
					}
				}
				// �ǂ��܂ŐL�΂��邩
				if (blocked <= 1 && connectNo > 1) {
					for (; countX <= BOARDSIZE && gomokuBoard[countX][countY] == EMPTY_SQUARE; countX++)
						emptySqCon++;
				}
				// �΂̘A���̎�ނ̐����X�V
				whiteConnectionAdmin(connectNo, blocked, emptySqCon);

				// �쓌����
				connectNo = 1;
				emptySqCon = 0;

				// �΂̘A���͔Ղ̒[������̐΂Ƀu���b�N����Ă���
				if (x == 1 || y == 1 || gomokuBoard[x - 1][y - 1] == BLACK_STONE)
					blocked = 1;
				else {
					blocked = 0;
					emptySqCon++;
				}

				// �΂̘A���𐔂���
				for (countX = x + 1, countY = y + 1; countX <= BOARDSIZE && countY <= BOARDSIZE; countX++, countY++)
				{
					if (gomokuBoard[countX][countY] == WHITE_STONE)
					{
						connectNo++;
					}
					else if (gomokuBoard[countX][countY] == BLACK_STONE)
					{
						blocked++;
						break;
					}
					else
					{
						break;
					}
				}
				// �ǂ��܂ŐL�΂��邩
				if (blocked <= 1 && connectNo > 1) {
					for (; countX <= BOARDSIZE && countY <= BOARDSIZE && gomokuBoard[countX][countY] == EMPTY_SQUARE; countX++, countY++)
						emptySqCon++;
				}
				// �΂̘A���̎�ނ̐����X�V
				whiteConnectionAdmin(connectNo, blocked, emptySqCon);

				// ������i���̏ꍇ�Ƀ_�u���J�E���g�͂Ȃ��̂Ŋm�F���Ȃ��Ă悢�j
				connectNo = 1;
				emptySqCon = 0;

				// �΂̘A���͔Ղ̒[������̐΂Ƀu���b�N����Ă���
				if (y == 1 || gomokuBoard[x][y - 1] == BLACK_STONE)
					blocked = 1;
				else {
					blocked = 0;
					emptySqCon++;
				}

				// �΂̘A���𐔂���
				countX = x;
				for (countY = y + 1; countY <= BOARDSIZE; countY++)
				{
					if (gomokuBoard[countX][countY] == WHITE_STONE)
					{
						connectNo++;
					}
					else if (gomokuBoard[countX][countY] == BLACK_STONE)
					{
						blocked++;
						break;
					}
					else
					{
						break;
					}
				}
				// �ǂ��܂ŐL�΂��邩
				if (blocked <= 1 && connectNo > 1) {
					for (; countY <= BOARDSIZE && gomokuBoard[countX][countY] == EMPTY_SQUARE; countY++)
						emptySqCon++;
				}
				// �΂̘A���̎�ނ̐����X�V
				whiteConnectionAdmin(connectNo, blocked, emptySqCon);

			}

			// �Ղ̒����ɋ߂��΂̕]������������
			if (side == BLACK && gomokuBoard[x][y] == BLACK_STONE)
				eval += potentialEvaluation[x][y];
			else if (side == WHITE && gomokuBoard[x][y] == WHITE_STONE)
				eval -= potentialEvaluation[x][y];
		}
	}

	// �A���ɒl��t����
	if ((blackOpenFour || blackClosedFour) && nextToMove == BLACK)
		eval = WINNING - (depth + 1);				// ���̎�Ԃƒ����S�̘A������A�󂢏����͐[���������ǂ�
	else if ((whiteOpenFour || whiteClosedFour) && nextToMove == WHITE)
		eval = -(WINNING - (depth + 1));		// ���̎�Ԃƒ����S�̘A������A�󂢏����͐[���������ǂ�
	else if (blackOpenFour >= 1)
		eval = WINNING - (depth + 2);				// ����Open Four�A�󂢏����͐[���������ǂ�
	else if (whiteOpenFour >= 1)
		eval = -(WINNING - (depth + 2));		// ����Open Four�A�󂢏����͐[���������ǂ�
	else if (blackClosedFour >= 2)
		eval = WINNING - (depth + 2);				// ���͘A���S���ȏオ����A�󂢏����͐[���������ǂ�
	else if (whiteClosedFour >= 2)
		eval = -(WINNING - (depth + 2));		// ���͘A���S���ȏオ����A�󂢏����͐[���������ǂ�
	else {
		// �ŋ���AI���e�X�gAI�̕]���l���g����
		if ((rootToMove == BLACK && blackPlayer == BEST_AI) ||
			(rootToMove == WHITE && whitePlayer == BEST_AI)) {
			//�@�����ȊO�̘A���̕]���i���j
			eval += blackClosedFour * bestEvalValues[CLOSED_FOUR_VALUE];
			eval += blackOpenThree * bestEvalValues[OPEN_THREE_VALUE];
			eval += blackClosedThree * bestEvalValues[CLOSED_THREE_VALUE];
			eval += blackOpenTwo * bestEvalValues[OPEN_TWO_VALUE];
			eval += blackClosedTwo * bestEvalValues[CLOSED_TWO_VALUE];

			//�@�����ȊO�̘A���̕]���i���j
			eval -= whiteClosedFour * bestEvalValues[CLOSED_FOUR_VALUE];
			eval -= whiteOpenThree * bestEvalValues[OPEN_THREE_VALUE];
			eval -= whiteClosedThree * bestEvalValues[CLOSED_THREE_VALUE];
			eval -= whiteOpenTwo * bestEvalValues[OPEN_TWO_VALUE];
			eval -= whiteClosedTwo * bestEvalValues[CLOSED_TWO_VALUE];

			// ��ԂɃ{�[�i�X
			if (nextToMove == BLACK)
			{
				eval += bestEvalValues[INITIATIVE];
			}
			else
			{
				eval -= bestEvalValues[INITIATIVE];
			}

		}
		else {
			//�@�����ȊO�̘A���̕]���i���j
			eval += blackClosedFour * testValues[CLOSED_FOUR_VALUE];
			eval += blackOpenThree * testValues[OPEN_THREE_VALUE];
			eval += blackClosedThree * testValues[CLOSED_THREE_VALUE];
			eval += blackOpenTwo * testValues[OPEN_TWO_VALUE];
			eval += blackClosedTwo * testValues[CLOSED_TWO_VALUE];

			//�@�����ȊO�̘A���̕]���i���j
			eval -= whiteClosedFour * testValues[CLOSED_FOUR_VALUE];
			eval -= whiteOpenThree * testValues[OPEN_THREE_VALUE];
			eval -= whiteClosedThree * testValues[CLOSED_THREE_VALUE];
			eval -= whiteOpenTwo * testValues[OPEN_TWO_VALUE];
			eval -= whiteClosedTwo * testValues[CLOSED_TWO_VALUE];

			// ��ԂɃ{�[�i�X
			if (nextToMove == BLACK)
			{
				eval += testValues[INITIATIVE];
			}
			else
			{
				eval -= testValues[INITIATIVE];
			}

		}

	}

	// ���ς��邽�߂ɗ�����ǉ�
	eval += (rand() % MAXRANDBONUS);

	// ���̕]���������琳���t
	if (side == WHITE)
		return -eval;

	return eval;
}

// �΂̘A���̎�ނ̐����X�V�i���̏ꍇ�j
void blackConnectionAdmin(int connectNo, int blocked, int openSquare)
{
	if (blocked >= 2) {
		// �A���͊��S�Ƀu���b�N����Ă���
	}
	else if (connectNo + openSquare < 5)
	{
		// �A���͂T�܂ŐL�΂��Ȃ�
	}
	else if (connectNo == 4)
	{
		// �����S�̘A���𔭌�����
		if (blocked == 0)
			blackOpenFour++;
		else if (blocked == 1)
			blackClosedFour++;
	}
	else if (connectNo == 3)
	{
		// �����R�̘A���𔭌�����
		if (blocked == 0)
			blackOpenThree++;
		else if (blocked == 1)
			blackClosedThree++;
	}
	else if (connectNo == 2)
	{
		// �����Q�̘A���𔭌�����
		if (blocked == 0)
			blackOpenTwo++;
		else if (blocked == 1)
			blackClosedTwo++;
	}
}

// �΂̘A���̎�ނ̐����X�V�i���̏ꍇ�j
void whiteConnectionAdmin(int connectNo, int blocked, int openSquare)
{
	if (blocked >= 2) {
		// �A���͊��S�Ƀu���b�N����Ă���
	}
	else if (connectNo + openSquare < 4)
	{
		// �A���͂T�܂ŐL�΂��Ȃ�
	}
	else if (connectNo == 4)
	{
		// �����S�̘A���𔭌�����
		if (blocked == 0)
			whiteOpenFour++;
		else if (blocked == 1)
			whiteClosedFour++;
	}
	else if (connectNo == 3)
	{
		// �����R�̘A���𔭌�����
		if (blocked == 0)
			whiteOpenThree++;
		else if (blocked == 1)
			whiteClosedThree++;
	}
	else if (connectNo == 2)
	{
		// �����Q�̘A���𔭌�����
		if (blocked == 0)
			whiteOpenTwo++;
		else if (blocked == 1)
			whiteClosedTwo++;
	}
}

