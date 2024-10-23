#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
bool creates_cycle(int loser, int winner);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Se name não é o nome de um candidato válido:
    for (int k = 0; k < candidate_count; k++)
    {
        if (strcmp(name, candidates[k]) == 0)
        {
            // Atualize ranks indicando que o eleitor tem o candidato como preferência no rank especificado
            ranks[rank] = k;
            // Retorne verdadeiro
            return true;
        }
    }
    // Se o nome não foi encontrado entre os candidatos válidos, retorne falso
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Para cada par de candidatos i e j, onde i é a preferência atual e j é a próxima preferência:
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Incrementar preferences[i][j]
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    // Para cada par de candidatos i e j, onde i é a preferência atual e j é a próxima preferência:
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Se preferences[i][j] > preferences[j][i]:
            if (preferences[i][j] > preferences[j][i])
            {
                // Adicione o par (i, j) ao array de pares
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            // Se preferences[j][i] > preferences[i][j]:
            else if (preferences[j][i] > preferences[i][j])
            {
                // Adicione o par (j, i) ao array de pares
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Ordenar o array de pares em ordem decrescente de força de vitória (strength of victory)
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            int strength1 = preferences[pairs[j].winner][pairs[j].loser];
            int strength2 = preferences[pairs[j + 1].winner][pairs[j + 1].loser];

            // Se a força de vitória do par atual for menor que a próxima, troque-os
            if (strength1 < strength2)
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        // Verificar se adicionar a aresta (winner, loser) cria um ciclo no grafo
        if (!creates_cycle(loser, winner))
        {
            // Adicionar a aresta (winner, loser) ao grafo (locked graph)
            locked[winner][loser] = true;
        }
    }
}

bool creates_cycle(int loser, int winner)
{
    if (loser == winner)
    {
        // Adicionar esta aresta criará um ciclo
        return true;
    }

    // Verificar recursivamente se adicionar a aresta cria um ciclo
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] && creates_cycle(i, winner))
        {
            return true;
        }
    }

    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // Para cada candidato i:
    for (int i = 0; i < candidate_count; i++)
    {
        int is_source = 1;

        // Verificar se i é o destino de alguma aresta no grafo (locked graph)
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                is_source = 0;
                break;
            }
        }

        // Se i não é o destino de nenhuma aresta no grafo (locked graph):
        if (is_source)
        {
            // Imprima o nome do candidato i como vencedor
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}
