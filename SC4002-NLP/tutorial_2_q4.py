# Q4. Write a program to do the following tasks:
# 1. Download the Web page of a given link and extract the text content of the page
# 2. Split the text into sentences and count sentences
# 3. Split the text into tokens and count token types
# 4. Find lemmas (or stems) of the tokens and count lemma types
# 5. Do stemming on the tokens and count unique ‘stemmed’ tokens
# You may use any tools, including nltk, LingPipe, and Stanford NLP software.

# Libraries - Installed in Python 3.11
import requests
from bs4 import BeautifulSoup
from nltk.stem import PorterStemmer
from nltk.tokenize import sent_tokenize, word_tokenize

# Article URL
articleURL = f"https://www.bbc.com/news/world-asia-66643667"

# 4a. Open the Article and Parse it as a Soup
articleResponse = requests.get(articleURL)
soup = BeautifulSoup(articleResponse.text, 'html.parser')
# Extract only the Text from the Paragraphs
articleBodyTextList = soup.find_all("p", "ssrcss-1q0x1qg-Paragraph e1jhz7w10")
articleBodyText = ""
for textElement in articleBodyTextList:
    articleBodyText += textElement.text
print(soup.title.contents)

# 4b. Split the Text into Sentences and Count the No. of Sentences
## Tokenise the text corpus by sentence
articleSentencesList = sent_tokenize(articleBodyText)
## Earlier returns a list of sentences
numSentences = len(articleSentencesList)
print("Number of Sentences: {}\n".format(numSentences))

# 4c. Split into tokens and count the Token Types {Unique Tokens} (However, assume they mean the number of any tokens for now)
## Segment based on words
articleWordsList = word_tokenize(articleBodyText)
numTokenTypes = len(articleWordsList)
print("Number of Token Types: {}\n".format(numTokenTypes))

# 4d. Find lemmas (or stems) of the tokens and count lemma types
## Create a Porter Stemmer
porterStemmer = PorterStemmer()
## Stem the words identified in the Words List
stemmedWordsList = []
for token in articleWordsList:
    stemmedWord = porterStemmer.stem(token)
    stemmedWordsList.append(stemmedWord)
print("Number of Lemma Types: {}\n".format(len(stemmedWordsList)))

# 4e. Do stemming on the tokens and count unique ‘stemmed’ tokens
## Determine the Unique Tokens
uniqueTokenTypeSet = set(stemmedWordsList)
print("Number of Unique Token Types: {}".format(len(uniqueTokenTypeSet)))