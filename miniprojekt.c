#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "v1.0"

void version()
{
	printf("%s\n", VERSION);
	puts(""); // for clear view
}

void help(char c[])
{
	version();
	printf("Usage: %s <template_id> [option]\n", c); // user input
	puts("");
	printf("Available options:\n");
	puts("");
	printf("-h, --help \t show this help\n");
	printf("-v, --version \t version info\n");
	printf("--stdout \t don't create source file, print result to stdout\n");
	puts("");
	printf("Available templates:\n");
	puts("");
	printf("* c \t\t - C source code [main.c]\n");
	printf("* cs \t\t - C# source code [Program.cs]\n");
	printf("* flask \t - Flask source code [app.py]\n");
	printf("* go \t\t - Go source code [main.go]\n");
	printf("* java \t\t - Java source code [Main.java]\n");
	printf("* nuon \t\t - prepare a virt. env. for Nushell [on]\n");
	printf("* py \t\t - Python 3 source code [main.py]\n");
	printf("* rust \t\t - Rust source code [main.rs]\n");
	printf("* sh \t\t - Bash source code [main.sh]\n");
	puts(""); // for clear view
}

void result_message(int set, char prompt[])
{
	if (set == 0) // 0 == file created
	{
		printf("\"%s\" was created", prompt); 
	} else // else 1 if error
	{
		printf("Error: the file \"%s\" already exists", prompt);
	}
	puts(""); // for clear view
}

char* source_code_name(char type[])
{
	if (strcmp(type, "c") == 0) return "main.c";
	if (strcmp(type, "cs") == 0) return "Program.cs";
	if (strcmp(type, "flask") == 0) return "app.py";
	if (strcmp(type, "go") == 0) return "main.go";
	if (strcmp(type, "java") == 0) return "Main.java";
	if (strcmp(type, "noun") == 0) return "on";
	if (strcmp(type, "py") == 0) return "main.py";
	if (strcmp(type, "rust") == 0) return "main.rs";
	if (strcmp(type, "sh") == 0) return "main.sh";
	// template was bad
	return "bad";
}

void generate_template(int type, int save_source, char stype[]) // 0 c | 1 cs ...
{
	// generate file 
	FILE *file;
	if (save_source == 1) file = fopen(source_code_name(stype), "w");
	
	if (type == 0) // c
	{
		fprintf(save_source == 1 ? file : stdout, "#include <stdio.h>\n\n");
		fprintf(save_source == 1 ? file : stdout, "int main()\n");
		fprintf(save_source == 1 ? file : stdout, "{\n");
		fprintf(save_source == 1 ? file : stdout, "    printf(\"Hello, world!\\n\");\n\n");
		fprintf(save_source == 1 ? file : stdout, "    return 0;\n}\n");
	}
	if (type == 1) // cs
	{
		fprintf(save_source == 1 ? file : stdout, "#include <stdio.h>\n\n");
		fprintf(save_source == 1 ? file : stdout, "int main()\n");
		fprintf(save_source == 1 ? file : stdout, "{\n");
		fprintf(save_source == 1 ? file : stdout, "    Console.WriteLine(\"{0}\", \"Hello, world!\");\n\n");
		fprintf(save_source == 1 ? file : stdout, "    return 0;\n}");
	}
	if (type == 2) // flask
	{
		fprintf(save_source == 1 ? file : stdout, "from flask import Flask\n");
		fprintf(save_source == 1 ? file : stdout, "app = Flask(__name__)\n\n");
		fprintf(save_source == 1 ? file : stdout, "@app.route('/')\n");
		fprintf(save_source == 1 ? file : stdout, "def hello_world():\n");
		fprintf(save_source == 1 ? file : stdout, "    return 'Hello, World!'\n\n");
		fprintf(save_source == 1 ? file : stdout, "if __name__ == '__main__':\n");
		fprintf(save_source == 1 ? file : stdout, "    app.run(debug=True)");
	}
	if (type == 3) // go
	{
		fprintf(save_source == 1 ? file : stdout, "package main;\n");
		fprintf(save_source == 1 ? file : stdout, "import \"fmt\";\n\n");
		fprintf(save_source == 1 ? file : stdout, "func main()\n");
		fprintf(save_source == 1 ? file : stdout, "{\n");
		fprintf(save_source == 1 ? file : stdout, "	fmt.Println(\"Hello, world!\")\n");
		fprintf(save_source == 1 ? file : stdout, "}");
	}
	if (type == 4) // java
	{
		fprintf(save_source == 1 ? file : stdout, "public class Main.java {\n");
		fprintf(save_source == 1 ? file : stdout, "    public static void main(String[] args) {\n");
		fprintf(save_source == 1 ? file : stdout, "        System.out.println(\"Hello, World!\");\n\n");
		fprintf(save_source == 1 ? file : stdout, "    }\n");
		fprintf(save_source == 1 ? file : stdout, "}");
	}
	if (type == 5) // noun
	{
		fprintf(save_source == 1 ? file : stdout, "echo 'Hello, World!'\n");
	}
	if (type == 6) // py
	{
		fprintf(save_source == 1 ? file : stdout, "def greet():\n");
		fprintf(save_source == 1 ? file : stdout, "    print(\"Hello, World!\")\n\n");
		fprintf(save_source == 1 ? file : stdout, "greet()");
	}
	if (type == 7) // rust
	{
		fprintf(save_source == 1 ? file : stdout, "fn main()\n");
		fprintf(save_source == 1 ? file : stdout, "{\n");
		fprintf(save_source == 1 ? file : stdout, "		println!(\"Hello, world!\");\n}");
		fprintf(save_source == 1 ? file : stdout, "}");
	}
	if (type == 8) // sh
	{
		fprintf(save_source == 1 ? file : stdout, "#!/bin/bash\n\n");
		fprintf(save_source == 1 ? file : stdout, "printf \"Hello, World!\\n\"\n");
	}
	
	fclose(file);
}

int main(int argc, char *argv[])
{
	// settings 
	
	int save_source = 1; // 1 to save || 0 to not (boolean)
	//teszt:? printf("%s %s %s\n\n", argv[0], argv[1], argv[2]);
	// -h --help
	
	if (argc == 1 || strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"--help") == 0)
	{
		help(argv[0]);
		exit(0);
	}
	
	// arguments
	
	if (strcmp(argv[1],"-v") == 0 || strcmp(argv[1],"--version") == 0) 
	{
		version();
		exit(0);
	}
	
	// --stdout
	
	if (argc >= 3)
	{
		if (strcmp(argv[2], "--stdout") == 0) 
		{ 
			save_source = 0;
		}		
	}
	
	// file already exists
	
	if (save_source == 1)
	{
		// file already exists
		FILE *file = fopen(source_code_name(argv[1]), "r");
    	if (!(file == NULL)) 
		{
        	result_message(1, source_code_name(argv[1]));
        	exit(1);
    	}

		fclose(file);
	}		

	// if template empty
	if (strcmp(argv[1], "") == 0)
	{
		printf("Error: no template selected\n");
		exit(1);
	}
	
	// if template bad
	if (strcmp(source_code_name(argv[1]), "bad") == 0) 
	{
		printf("Error: template do not exists (-h or --help for help)\n");
		exit(1);
	} else
	{ 		// make template
		if (strcmp(argv[1],"c") == 0) generate_template(0, save_source, argv[1]);
		if (strcmp(argv[1],"cs") == 0) generate_template(1, save_source, argv[1]);
		if (strcmp(argv[1],"flask") == 0) generate_template(2, save_source, argv[1]);
		if (strcmp(argv[1],"go") == 0) generate_template(3, save_source, argv[1]);
		if (strcmp(argv[1],"java") == 0) generate_template(4, save_source, argv[1]);
		if (strcmp(argv[1],"noun") == 0) generate_template(5, save_source, argv[1]);
		if (strcmp(argv[1],"py") == 0) generate_template(6, save_source, argv[1]);
		if (strcmp(argv[1],"rust") == 0) generate_template(7, save_source, argv[1]);
		if (strcmp(argv[1],"sh") == 0) generate_template(8, save_source, argv[1]);
	}
	
	if (save_source == 1) result_message(0, source_code_name(argv[1]));
	
	return 0;
}

// 2024 Koszta Félix