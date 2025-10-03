#include <stdio.h>
#include <stdlib.h>
#define MAX_TOKENS 31

typedef struct Ttokens {
    int m_NorthTokens[MAX_TOKENS];
    int northTokensSize;
    int m_SouthTokens[MAX_TOKENS];
    int southTokensSize;
    int m_WestTokens[MAX_TOKENS];
    int westTokensSize;
    int m_EastTokens[MAX_TOKENS];
    int eastTokensSize;
} Ttokens;

int readTokens(Ttokens * tokens)
{
    char cardinalDirection;
    char openBracket, separator;
    int token;
    printf("Zetony:\n");
    while ( scanf(" %c:", &cardinalDirection) == 1 )
    {
        int count = 0;
        if ( scanf( " %c ", &openBracket ) != 1 
            || openBracket != '{' )
        {
            return 0;
        }

        while ( 1 )
        {
            if ( scanf( "%d %c ", &token, &separator ) != 2 
                || ( separator != ',' && separator != '}' ) )
            {
                return 0;
            }

            switch (cardinalDirection)
            {
            case 'S':
                if (tokens->southTokensSize > 0 && count == 0)
                    return 0;
                tokens->m_SouthTokens[count] = token;
                tokens->southTokensSize++;
                count++;
                break;
            case 'N':
                if (tokens->northTokensSize > 0 && count == 0)
                    return 0;
                tokens->m_NorthTokens[count] = token;
                tokens->northTokensSize++;
                count++;
                break;
            case 'W':
                if (tokens->westTokensSize > 0 && count == 0)
                    return 0;
                tokens->m_WestTokens[count] = token;
                tokens->westTokensSize++;
                count++;
                break;
            case 'E':
                if (tokens->eastTokensSize > 0 && count == 0)
                    return 0;
                tokens->m_EastTokens[count] = token;
                tokens->eastTokensSize++;
                count++;
                break;
            default:
                return 0;
            }
            if (count > 31)
                return 0;

            if ( separator == '}' )
                break;
        }
    }
    if (tokens->eastTokensSize == 0 || tokens->northTokensSize == 0 || tokens->southTokensSize == 0 || tokens->westTokensSize == 0)
        return 0;
    
    return 1;
}

int main ( void )
{
    // initialize the tokens
    Ttokens tokens = {  };

    // read the input and validate it
    if ( !readTokens(&tokens)){
        printf("Nespravny vstup.\n");
        return 0;
    }

    return 0;
} 
