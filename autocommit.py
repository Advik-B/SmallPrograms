# Makes my commits look like I'm working hard
import subprocess

# Run git reset to unstage any files
subprocess.run(['git', 'reset'], stdout=subprocess.PIPE, shell=True)

# Run git status to see if there are any changes
status_output = subprocess.run(
    ['git', 'status', '--porcelain'],
    stdout=subprocess.PIPE,
    shell=True,
)

if status_output.stdout:
    for line in status_output.stdout.splitlines():

        # Get the filename
        filename = line[3:].decode('utf-8')
        # Status of the file
        status = line[:2].decode('utf-8')
        # Add the file to the staging area
        # subprocess.run(['git', 'add', filename])

        status = status.strip()
        # Convert the status to a human readable format

        filestatus: str
        if status == 'A':
            filestatus = 'added'
        elif status == 'D':
            filestatus = 'deleted'
        elif status in ['M', 'MM']:
            filestatus = 'modified'
        elif status == 'R':
            filestatus = 'renamed'
        elif status == 'C':
            filestatus = 'copied'
        elif status == 'U':
            filestatus = 'updated but unmerged'
        elif status == '??':
            filestatus = 'untracked'
        else:
            filestatus = "?"
        # Commit the file
        subprocess.run(['git', 'add', filename])
        subprocess.run(['git', 'commit', '-m', f'{filestatus}: {filename}'])