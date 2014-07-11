#include "tools.h"

Dlfile * download(const char * str_url) {
    struct      url_stat st;
    fetchIO     *f = NULL;
    Dlfile      *file = NULL;
    size_t      buf_len,buf_fetched;
    ssize_t     cur_fetched;
    size_t      fetch_buffer = 1024;
    struct url  *url;

    url = fetchParseURL(str_url);

    if (url == NULL || (f = fetchXGetURL(str_url, &st, "")) == NULL)
        // XXX: return NULL instead of quitting 
        quit("Failed to fetch");

    if (st.size == -1)
        // XXX
        quit("Invalid file");

    buf_len = (size_t)st.size;
    file = xmalloc(sizeof(Dlfile));
    file->buf = xmalloc(buf_len + 1);

    buf_fetched = 0;

    while (buf_fetched < buf_len) {
        cur_fetched = fetchIO_read(f, file->buf + buf_fetched,
                fetch_buffer);
        if (cur_fetched == 0)
            // XXX
            quit("truncated file");
        else if (cur_fetched == -1)
            // XXX
            quit("truncated file\n");
        buf_fetched += (size_t)cur_fetched;
    }

    file->buf[buf_len] = '\0';
    file->size = buf_len;

    if (file->buf[0] == '\0')
        quit("empty download");

    fetchIO_close(f);

    return file;
}

void output_file(const char * name, const char * url, Dlfile * f) {
    FILE *fp;

    f = download(url);

    if (f) {
        if ((fp = fopen(name, "w")) == NULL)
            quit("failed to open file");

        fwrite(f->buf, f->size, 1, fp);

        fclose(fp);
        free(f->buf);
        f->buf = NULL;
        free(f);
        f = NULL;
    }
}

void help(void) {
    quit("./fetch -s <url> -o <output file name>");
}

int quit(const char * msg) {
    fprintf(stderr, "quit : %s\n", msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    Dlfile *ar = NULL;
    char *url = NULL; 
    char *file = NULL;
    int c;

    if (argc >= 2) {
        while ((c = getopt(argc, argv, "hs:o:")) != -1) {
            switch(c) {
                case 's' : 
                    url = strndup(optarg, BUFSIZ);
                    break;
                case 'o' :
                    if (url == NULL)
                        help();
                    else
                        file = strndup(optarg, BUFSIZ);
                    break;
                case 'h':
                default : 
                    help(); 
            }
        }
    } else {
        help();
    }

    output_file(file, url, ar);

    free(url);
    url = NULL;
    free(file);
    file = NULL;

    return 0;
}
