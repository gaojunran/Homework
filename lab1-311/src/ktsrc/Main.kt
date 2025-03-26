package ktsrc

data class NFA(
    val cardinality: Int,
    val alphabet: Set<Char>,
    val finalStates: Set<Int>,
    val startState: Int,
    val transitions: Set<Transition>
)

data class Transition(
    val fromState: Int,
    val input: Char,
    val toState: Int
)

data class DFA(
    val cardinality: Int,
    val alphabet: Set<Char>,
    val finalStates: Set<Int>,
    val startState: Int,
    val transitions: Set<Transition>
) {
    fun output() {
        println(cardinality)
        println(alphabet.joinToString(""))
        println(finalStates.joinToString(" "))
        println(startState)
        transitions.forEach {
            println("${it.fromState} ${it.input} ${it.toState}")
        }
    }
}

fun convertNFAToDFA(nfa: NFA): DFA {
    val dfaTransitions = mutableSetOf<Transition>()
    val stateMapping = mutableMapOf<Set<Int>, Int>() // Map to store NFA state sets to DFA state IDs
    val queue = ArrayDeque<Set<Int>>() // Queue to process subset states

    val startSet = setOf(nfa.startState) // Initial DFA state from NFA start state
    queue.add(startSet)
    stateMapping[startSet] = 0

    val dfaFinalStates = mutableSetOf<Int>()
    val dfaAlphabet = nfa.alphabet
    var stateCounter = 1

    while (queue.isNotEmpty()) {
        val currentStateSet = queue.removeFirst()
        val dfaStateId = stateMapping[currentStateSet]!!

        // Check if the current DFA state contains any NFA final states
        if (currentStateSet.any { it in nfa.finalStates }) {
            dfaFinalStates.add(dfaStateId)
        }

        // Process each input symbol
        for (symbol in dfaAlphabet) {
            // Compute the set of next NFA states for the current input symbol and current NFA state
            val nextStateSet = currentStateSet.flatMap { state ->
                nfa.transitions.filter { it.fromState == state && it.input == symbol }.map { it.toState }
            }.toSet()

            if (nextStateSet.isNotEmpty()) {
                if (nextStateSet !in stateMapping) {
                    // Assign a new DFA state ID to the next NFA state set
                    stateMapping[nextStateSet] = stateCounter++
                    queue.add(nextStateSet)
                }

                dfaTransitions.add(
                    Transition(dfaStateId, symbol, stateMapping[nextStateSet]!!)
                )
            }
        }
    }

    return DFA(
        cardinality = stateMapping.size, // Total number of states in DFA
        alphabet = dfaAlphabet, // Same alphabet as NFA
        finalStates = dfaFinalStates, // Computed final states in DFA
        startState = stateMapping[startSet]!!, // Start state of DFA
        transitions = dfaTransitions // DFA transitions
    )
}




fun main() {
    val cardinality = readln().toInt()
    val alphabet = readln().toCharArray().toSet()
    val finalStates = readln().split(" ").map { it.toInt() }.toSet()
    val startState = readln().toInt()
    val transitions = mutableSetOf<Transition>()
    while (true) {
        val line = readln()
        if (line == "") break
        val (fromState, input, toState) = line.split(" ")
        transitions.add(Transition(fromState.toInt(), input[0], toState.toInt()))
    }
    val nfa = NFA(cardinality, alphabet, finalStates, startState, transitions)
    val dfa = convertNFAToDFA(nfa)
    dfa.output()
}


