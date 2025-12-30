import os

if __name__ == "__main__":
    filepath = input("Filepath: (will default to ~/.zshrc)").strip()
    filepath = os.path.expanduser(filepath if filepath else "~/.zshrc")
    content = """
# Enable Zsh completion system
autoload -Uz compinit
compinit

typeset -A dp_dirs
dp_dirs=(
    tmod "$HOME/Library/Application Support/Terraria/tModLoader/Mods"
    github "$HOME/codingprojects/github"
    python "$HOME/codingprojects/python"
    cproj "$HOME/codingprojects"
    sysAPS "$HOME/Library/Application Support"
)

function cd() {
    if [[ "$1" == dp.* ]]; then
        local key="${1#dp.}"
        local target="${dp_dirs[$key]}"
        if [[ -n "$target" ]]; then
            builtin cd "$target" || return
        else
            echo "dp: unknown target '$key'"
            return 1
        fi
    else
        builtin cd "$@" || return
    fi
}

# Tab completion for dp.*
function _dp_cd_completion() {
    local -a keys
    keys=("${(@k)dp_dirs}")  # get all keys from associative array
    compadd dp."$keys[@]"    # add dp.<key> options
}

compdef _dp_cd_completion cd

"""
    with open(filepath, "a+") as file:
        write = file.write
        write("# Added by DevCLI.devpaths")
        write(content)
        write("# End devcli.devpaths")