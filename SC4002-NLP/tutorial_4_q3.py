from hmmlearn import hmm
import numpy as np

# Defining my own Hidden Markov Model. I would have 2 hidden states since I am modelling the weather forecast as the states
hiddenStates = 2
hiddenMarkovModel = hmm.MultinomialHMM(n_components=hiddenStates)

# Set Transition Probabilities
# Each row corresponds to a source state, and each column corresponds to a target state. 
# The element at row i and column j represents the probability of transitioning from state i to state j.
hiddenMarkovModel.transmat_ = np.array([
    [0.7, 0.3],
    [0.4, 0.6]
])
##      HOT COLD
## HOT
## COLD             for the above matrix

# Set Emission Probabilities, which describe the probabilities of emitting specific observations or symbols when in a particular hidden state.
hiddenMarkovModel.emissionprob_ = np.array([
    [0.2, 0.4, 0.4],
    [0.5, 0.4, 0.1]
])
## Observations: 1  2   3
## HOT
## COLD

# Define the Observation Sequence
obsSeq1 = np.array([3, 1, 2, 3, 1, 2, 3, 1, 2])
obsSeq2 = np.array([3, 1, 1, 2, 3, 3, 1, 1, 2])

# Run the Viterbi Algo on each sequence to compute most likely weather condition
weatherSeq1 = hiddenMarkovModel.predict(obsSeq1.reshape(-1, 1))
weatherSeq2 = hiddenMarkovModel.predict(obsSeq2.reshape(-1, 1))

# Interpret the results
print("Most likely weather sequence for Sequence 1:", weatherSeq1)
print("Most likely weather sequence for Sequence 2:", weatherSeq2)
