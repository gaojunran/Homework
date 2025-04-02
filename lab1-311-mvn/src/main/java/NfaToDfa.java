import java.util.*;

class NFA {
    int cardinality;
    Set<Character> alphabet;
    Set<Integer> finalStates;
    int startState;
    Set<Transition> transitions;

    public NFA(int cardinality, Set<Character> alphabet, Set<Integer> finalStates, int startState, Set<Transition> transitions) {
        this.cardinality = cardinality;
        this.alphabet = alphabet;
        this.finalStates = finalStates;
        this.startState = startState;
        this.transitions = transitions;
    }
}

class Transition {
    int fromState;
    char input;
    int toState;

    public Transition(int fromState, char input, int toState) {
        this.fromState = fromState;
        this.input = input;
        this.toState = toState;
    }
}

class DFA {
    int cardinality;
    Set<Character> alphabet;
    Set<Integer> finalStates;
    int startState;
    Set<Transition> transitions;

    public DFA(int cardinality, Set<Character> alphabet, Set<Integer> finalStates, int startState, Set<Transition> transitions) {
        this.cardinality = cardinality;
        this.alphabet = alphabet;
        this.finalStates = finalStates;
        this.startState = startState;
        this.transitions = transitions;
    }

    public void output() {
        System.out.println(cardinality);
        for (char c : alphabet) {
            System.out.print(c);
        }
        System.out.println();
        for (int state : finalStates) {
            System.out.print(state + " ");
        }
        System.out.println();
        System.out.println(startState);
        for (Transition t : transitions) {
            System.out.println(t.fromState + " " + t.input + " " + t.toState);
        }
    }
}

public class NfaToDfa {
    public static DFA convertNFAToDFA(NFA nfa) {
        Set<Transition> dfaTransitions = new HashSet<>();
        Map<Set<Integer>, Integer> stateMapping = new HashMap<>(); // Map to store NFA state sets to DFA state IDs
        Queue<Set<Integer>> queue = new ArrayDeque<>(); // Queue to process subset states

        Set<Integer> startSet = new HashSet<>();
        startSet.add(nfa.startState); // Initial DFA state from NFA start state
        queue.add(startSet);
        stateMapping.put(startSet, 0);

        Set<Integer> dfaFinalStates = new HashSet<>();
        Set<Character> dfaAlphabet = nfa.alphabet;
        int stateCounter = 1;

        while (!queue.isEmpty()) {
            Set<Integer> currentStateSet = queue.poll();
            int dfaStateId = stateMapping.get(currentStateSet);

            // Check if the current DFA state contains any NFA final states
            if (!Collections.disjoint(currentStateSet, nfa.finalStates)) {
                dfaFinalStates.add(dfaStateId);
            }

            // Process each input symbol
            for (char symbol : dfaAlphabet) {
                // Compute the set of next NFA states for the current input symbol and current NFA state
                Set<Integer> nextStateSet = new HashSet<>();
                for (int state : currentStateSet) {
                    for (Transition t : nfa.transitions) {
                        if (t.fromState == state && t.input == symbol) {
                            nextStateSet.add(t.toState);
                        }
                    }
                }
                if (!nextStateSet.isEmpty()) {
                    if (!stateMapping.containsKey(nextStateSet)) {
                        // Assign a new DFA state ID to the next NFA state set
                        stateMapping.put(nextStateSet, stateCounter++);
                        queue.add(nextStateSet);
                    }
                    dfaTransitions.add(new Transition(dfaStateId, symbol, stateMapping.get(nextStateSet)));
                }
            }
        }

        return new DFA(
                stateMapping.size(), // Total number of states in DFA
                dfaAlphabet, // Same alphabet as NFA
                dfaFinalStates, // Computed final states in DFA
                stateMapping.get(startSet), // Start state of DFA
                dfaTransitions // DFA transitions
        );
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int cardinality = Integer.parseInt(scanner.nextLine());
        Set<Character> alphabet = new HashSet<>();
        for (char c : scanner.nextLine().toCharArray()) {
            alphabet.add(c);
        }
        Set<Integer> finalStates = new HashSet<>();
        for (String s : scanner.nextLine().split(" ")) {
            finalStates.add(Integer.parseInt(s));
        }
        int startState = Integer.parseInt(scanner.nextLine());
        Set<Transition> transitions = new HashSet<>();
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            if (line.isEmpty()) break;
            String[] parts = line.split(" ");
            transitions.add(new Transition(Integer.parseInt(parts[0]), parts[1].charAt(0), Integer.parseInt(parts[2])));
        }
        scanner.close();

        NFA nfa = new NFA(cardinality, alphabet, finalStates, startState, transitions);
        DFA dfa = convertNFAToDFA(nfa);
        dfa.output();
    }
}
