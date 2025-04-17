// Define a structure to represent a transition
typedef struct {
  int fromState;
  char input;
  int toState;
} Transition;

// Define a structure to represent an NFA
typedef struct {
  int cardinality; // Number of states
  char alphabet[256]; // Set of input symbols
  int finalStates[100]; // Set of final states
  int finalStateCount; // Number of final states
  int startState; // Start state
  Transition transitions[1000]; // Set of transitions
  int transitionCount; // Number of transitions
} NFA;

// Define a structure to represent a DFA
typedef struct {
  int cardinality; // Number of states
  char alphabet[256]; // Set of input symbols
  int finalStates[100]; // Set of final states
  int finalStateCount; // Number of final states
  int startState; // Start state
  Transition transitions[1000]; // Set of transitions
  int transitionCount; // Number of transitions
} DFA;

// Function to check if a character is in the alphabet
int isInAlphabet(char alphabet[256], char c) {
  return alphabet[(int)c] == 1;
}

// Function to add a character to the alphabet
void addToAlphabet(char alphabet[256], char c) {
  alphabet[(int)c] = 1;
}

// Function to check if a state is in the final states
int isFinalState(int finalStates[100], int finalStateCount, int state) {
  for (int i = 0; i < finalStateCount; i++) {
      if (finalStates[i] == state) {
          return 1;
      }
  }
  return 0;
}

// Function to convert an NFA to a DFA
DFA convertNFAToDFA(NFA nfa) {
  DFA dfa;
  int stateMapping[1000][100]; // Maps NFA state sets to DFA state IDs
  int stateMappingCount = 0;
  int queue[1000][100]; // Queue to process subset states
  int queueFront = 0, queueRear = 0;

  // Initialize the start state of the DFA
  int startSet[100] = {0};
  startSet[0] = nfa.startState;
  queue[queueRear++][0] = nfa.startState;
  stateMapping[stateMappingCount++][0] = nfa.startState;

  int dfaFinalStates[100] = {0};
  int dfaFinalStateCount = 0;
  memcpy(dfa.alphabet, nfa.alphabet, 256);
  int stateCounter = 1;

  while (queueFront < queueRear) {
      int currentStateSet[100];
      memcpy(currentStateSet, queue[queueFront++], sizeof(currentStateSet));
      int dfaStateId = stateMappingCount - 1;

      // Check if the current DFA state contains any NFA final states
      for (int i = 0; i < nfa.cardinality; i++) {
          if (isFinalState(nfa.finalStates, nfa.finalStateCount, currentStateSet[i])) {
              dfaFinalStates[dfaFinalStateCount++] = dfaStateId;
              break;
          }
      }

      // Process each input symbol
      for (int i = 0; i < 256; i++) {
          if (isInAlphabet(nfa.alphabet, i)) {
              int nextStateSet[100] = {0};
              int nextStateCount = 0;

              // Compute the set of next NFA states for the current input symbol and current NFA state
              for (int j = 0; j < nfa.cardinality; j++) {
                  for (int k = 0; k < nfa.transitionCount; k++) {
                      if (nfa.transitions[k].fromState == currentStateSet[j] && nfa.transitions[k].input == i) {
                          nextStateSet[nextStateCount++] = nfa.transitions[k].toState;
                      }
                  }
              }

              // If there are next states, add a transition to the DFA
              if (nextStateCount > 0) {
                  int nextStateSetHash = 0;
                  for (int j = 0; j < nextStateCount; j++) {
                      nextStateSetHash += nextStateSet[j];
                  }

                  int found = 0;
                  for (int j = 0; j < stateMappingCount; j++) {
                      int stateSetHash = 0;
                      for (int k = 0; k < nfa.cardinality; k++) {
                          stateSetHash += stateMapping[j][k];
                      }
                      if (stateSetHash == nextStateSetHash) {
                          found = 1;
                          dfa.transitions[dfa.transitionCount++] = (Transition){dfaStateId, i, j};
                          break;
                      }
                  }

                  if (!found) {
                      stateMapping[stateMappingCount++][0] = nextStateSet[0];
                      queue[queueRear++][0] = nextStateSet[0];
                      dfa.transitions[dfa.transitionCount++] = (Transition){dfaStateId, i, stateCounter++};
                  }
              }
          }
      }
  }

  dfa.cardinality = stateCounter;
  dfa.startState = 0;
  dfa.finalStateCount = dfaFinalStateCount;
  memcpy(dfa.finalStates, dfaFinalStates, sizeof(dfaFinalStates));
  return dfa;
}

// Function to output the DFA structure
void outputDFA(DFA dfa) {
  printf("%d\n", dfa.cardinality);
  for (int i = 0; i < 256; i++) {
      if (isInAlphabet(dfa.alphabet, i)) {
          putchar(i);
      }
  }
  printf("\n");
  for (int i = 0; i < dfa.finalStateCount; i++) {
      printf("%d ", dfa.finalStates[i]);
  }
  printf("\n");
  printf("%d\n", dfa.startState);
  for (int i = 0; i < dfa.transitionCount; i++) {
      printf("%d %c %d\n", dfa.transitions[i].fromState, dfa.transitions[i].input, dfa.transitions[i].toState);
  }
}

int main() {
  NFA nfa;
  printf("Enter number of states:\n");
  scanf("%d", &nfa.cardinality);

  printf("Enter alphabet (characters without spaces, e.g., abc):\n");
  char alphabetInput[256];
  scanf("%s", alphabetInput);
  memset(nfa.alphabet, 0, 256);
  for (int i = 0; alphabetInput[i] != '\0'; i++) {
      addToAlphabet(nfa.alphabet, alphabetInput[i]);
  }

  printf("Enter number of final states followed by the final states (e.g., 2 1 3):\n");
  scanf("%d", &nfa.finalStateCount);
  for (int i = 0; i < nfa.finalStateCount; i++) {
      scanf("%d", &nfa.finalStates[i]);
  }

  printf("Enter start state:\n");
  scanf("%d", &nfa.startState);

  printf("Enter transitions (format: fromState inputSymbol toState), one per line. Enter an empty line to finish:\n");
  nfa.transitionCount = 0;
  while (1) {
      char line[256];
      if (fgets(line, sizeof(line), stdin) == NULL || strcmp(line, "\n") == 0) {
          break;
      }
      int fromState, toState;
      char input;
      sscanf(line, "%d %c %d", &fromState, &input, &toState);
      nfa.transitions[nfa.transitionCount++] = (Transition){fromState, input, toState};
  }

  DFA dfa = convertNFAToDFA(nfa);
  outputDFA(dfa);

  return 0;
}
