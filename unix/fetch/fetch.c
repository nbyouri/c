/*
 *
 *
 * Fetch : Youri Mouton 11 July 2014.
 *
 * Dependencies : libfetch, openssl, xmalloc, progressmeter
 *
 */ 
#include "tools.h"

Dlfile * download(const char * str_url) {
    struct      url_stat st;
    fetchIO     *f = NULL;
    Dlfile      *file = NULL;
    size_t      buf_len,buf_fetched;
    ssize_t     cur_fetched;
    size_t      fetch_buffer = 1024;
    struct url  *url;
    char        *p;
    off_t       statsize;

    url = fetchParseURL(str_url);

    if (url == NULL || (f = fetchXGetURL(str_url, &st, "")) == NULL)
        fatal("Failed to fetch\n");

    if (st.size == -1)
        fatal("Invalid file\n");

    if ((p = strrchr(str_url, '/')) != NULL)
        p++;
    else
        p = (char *)str_url;

    buf_len = (size_t)st.size;
    file = xmalloc(sizeof(Dlfile));
    file->buf = xmalloc(buf_len + 1);

    buf_fetched = 0;
    statsize = 0;

    start_progress_meter(p, buf_len, &statsize);

    while (buf_fetched < buf_len) {
        cur_fetched = fetchIO_read(f, file->buf + buf_fetched, fetch_buffer);
        if (cur_fetched == 0)
            fatal("truncated file\n");
        else if (cur_fetched == -1)
            fatal("truncated file\n");
        buf_fetched += (size_t)cur_fetched;
        statsize += (size_t)cur_fetched;
    }

    stop_progress_meter();

    file->buf[buf_len] = '\0';
    file->size = buf_len;

    if (file->buf[0] == '\0')
        fatal("empty download\n");

    fetchIO_close(f);

    return file;
}

void output_file(const char * name, const char * url, Dlfile * f) {
    FILE *fp;

    f = download(url);

    if (f) {
        if ((fp = fopen(name, "w")) == NULL)
            fatal("failed to open file\n");

        fwrite(f->buf, f->size, 1, fp);

        fclose(fp);
        free(f->buf);
        f->buf = NULL;
        free(f);
        f = NULL;
    }
}

void help(void) {
    fatal("./fetch -s <url> -o <output file name>");
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
                    url = xstrdup(optarg);
                    break;
                case 'o' :
                    if (url == NULL)
                        help();
                    else
                        file = xstrdup(optarg);
                    break;
                case 'h':
                default : 
                    help(); 
            }
        }
    } else
        help();

    output_file(file, url, ar);

    free(ar);
    ar = NULL;
    free(url);
    url = NULL;
    free(file);
    file = NULL;

    return 0;
}
