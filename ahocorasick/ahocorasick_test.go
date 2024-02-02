package ahocorasick

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strings"
	"testing"
)

func ReadFromFile() []string {
	text := make([]string, 0)

	f, err := os.Open("file/dirty_word_info_data.csv")
	if err != nil {
		log.Fatal(err)
		return text
	}

	defer f.Close()

	scanner := bufio.NewScanner(f)
	for scanner.Scan() {
		//fmt.Printf("line:%s\n", scanner.Text())
		text = append(text, scanner.Text())
	}

	if err := scanner.Err(); err != nil {
		log.Fatal(err)
	}

	return text
}

func TestAhocorasickMany(t *testing.T) {
	words := ReadFromFile()
	if len(words) == 0 {
		t.Errorf("no file")
		return
	}

	ac := NewAcTrie()

	keyWords := make([]string, 0, len(words))
	for i := 1; i < len(words); i++ {
		str := strings.Split(words[i], ",")
		if len(str) != 2 {
			continue
		}

		word := strings.TrimSpace(str[1])
		if len(word) == 0 {
			continue
		}

		keyWords = append(keyWords, word)
	}
	ac.BuildTrie(keyWords)

	ac.BuildFailPointer()

	content := "0123456祝你生日快乐生日快乐不思蜀！1565456aquajackcarecardcatdogcancare"
	content = strings.TrimSpace(content)
	result := ac.Search(content)
	for _, res := range result {
		fmt.Printf("%-3d %-3d %v %s\n", res.Begin, res.End, res.Value, string(res.Value))
	}
}

func TestAhocorasick(t *testing.T) {
	ac := NewAcTrie()

	words := []string{"aquaj", "jack", "ack", "card", "care"}
	//words := []string{"i", "is", "he", "his", "she", "hers"}
	ac.BuildTrie(words)
	ac.BuildFailPointer()

	content := "aquajackcarecardcatdogcancare"
	//content := "she is hers"
	result := ac.Search(content)
	for _, res := range result {
		fmt.Printf("%-3d %-3d %s\n", res.Begin, res.End, string(res.Value))
	}
}
