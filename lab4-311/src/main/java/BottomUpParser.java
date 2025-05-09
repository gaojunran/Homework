import java.util.*;

public class BottomUpParser {

    // Grammar rules: ruleIndex from 0 to 2
    static class Rule {
        String lhs;
        String rhs;
        Rule(String lhs, String rhs) {
            this.lhs = lhs;
            this.rhs = rhs;
        }
    }

    static final Rule[] rules = {
        new Rule("S", "X"),      // Rule 1: <S> → <X>
        new Rule("X", "(X)"),    // Rule 2: <X> → (<X>)
        new Rule("X", "()")      // Rule 3: <X> → ()
    };

    // ACTION table: actionTable[state][symbol] => action string (e.g., "s2", "r1", "acc")
    static final Map<Integer, Map<String, String>> actionTable = new HashMap<>();
    static {
        actionTable.put(0, Map.of("(", "s2"));
        actionTable.put(1, Map.of("$", "acc"));
        actionTable.put(2, Map.of("(", "s2", ")", "s5"));
        actionTable.put(3, Map.of(")", "s4"));
        actionTable.put(4, Map.of("(", "r2", ")", "r2", "$", "r2"));
        actionTable.put(5, Map.of("(", "r3", ")", "r3", "$", "r3"));
    }

    // GOTO table: gotoTable[state][nonterminal] => new state
    static final Map<Integer, Map<String, Integer>> gotoTable = new HashMap<>();
    static {
        gotoTable.put(0, Map.of("X", 1));
        gotoTable.put(2, Map.of("X", 3));
    }

    static Stack<Integer> stateStack = new Stack<>();
    static Stack<String> symbolStack = new Stack<>();

    public static void main(String[] args) {
        String[] testInputs = { "(())$", "((()))$", "($" };
        for (String input : testInputs) {
            System.out.println("\nParsing input: " + input);
            parseInput(input);
        }
    }

    static void parseInput(String input) {
        stateStack.clear();
        symbolStack.clear();
        // initial state: s0
        stateStack.push(0);
        // track the current char index in the input
        int index = 0;
        while (true) {
            int state = stateStack.peek();
            String symbol = String.valueOf(input.charAt(index));

            String action = getAction(state, symbol);

            if (action == null) {
                System.out.println("Error: Unexpected symbol '" + symbol + "' in state s" + state);
                return;
            }

            if (action.equals("acc")) {
                System.out.println("Accepted!");
                return;
            }

            if (action.startsWith("s")) {
                int newState = Integer.parseInt(action.substring(1));
                shift(newState, symbol);
                index++;
            } else if (action.startsWith("r")) {
                int ruleIndex = Integer.parseInt(action.substring(1)) - 1; // 1-based to 0-based
                reduce(ruleIndex);
            } else {
                System.out.println("Error: Invalid action '" + action + "'");
                return;
            }
        }
    }

    static void shift(int newState, String symbol) {
        symbolStack.push(symbol);
        stateStack.push(newState);
        System.out.println("Shift: push symbol '" + symbol + "', go to state s" + newState);
    }

    static void reduce(int ruleIndex) {
        Rule rule = rules[ruleIndex];
        int popCount = rule.rhs.length();
        // pop together
        for (int i = 0; i < popCount; i++) {
            if (!symbolStack.isEmpty()) symbolStack.pop();
            if (!stateStack.isEmpty()) stateStack.pop();
        }
        // push symbol
        symbolStack.push(rule.lhs);
        int currentState = stateStack.peek();

        Map<String, Integer> gotoRow = gotoTable.get(currentState);
        if (gotoRow == null || !gotoRow.containsKey(rule.lhs)) {
            System.out.println("Error: No GOTO entry for state s" + currentState + " and symbol '" + rule.lhs + "'");
            return;
        }

        int newState = gotoRow.get(rule.lhs);
        // find new state in goto table and push it
        stateStack.push(newState);
        System.out.println("Reduce: apply rule " + (ruleIndex + 1) + " (" + rule.lhs + " → " + rule.rhs + "), goto state s" + newState);
    }

    static String getAction(int state, String symbol) {
        Map<String, String> row = actionTable.get(state);
        return (row != null) ? row.getOrDefault(symbol, null) : null;
    }
}
