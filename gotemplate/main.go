package main

import (
	"fmt"
	"os"
)

func main() {

	if len(os.Args) < 2 {
		fmt.Println("Usage: go run cd.go <directory>")
		return
	}

	err := os.Mkdir(os.Args[1], 0755)
	if err != nil && !os.IsExist(err) {
		fmt.Println("Error:", err)
		return
	}

	// Change to that directory
	err = os.Chdir(os.Args[1])
	if err != nil {
		fmt.Println("Error changing directory:", err)
		return
	}

	// Confirm we’re inside
	dir, _ := os.Getwd()
	fmt.Println("Now inside:", dir)
	content := "package main\n\nimport (\n	\"fmt\"\n)\n\nfunc main() {\n	fmt.Println(\"\")\n}"

	// Create or overwrite the file
	enrr := os.WriteFile("main.go", []byte(content), 0644)
	if enrr != nil {
		fmt.Println("Error:", err)
		return
	}
}
