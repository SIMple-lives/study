#include <gtk/gtk.h>
#include <dirent.h>
#include <sys/stat.h>

// 在窗口中显示目录内容
void show_directory(GtkWidget *widget, gpointer window) {
    GtkWidget *dialog = gtk_file_chooser_dialog_new("选择目录",
        GTK_WINDOW(window),
        GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
        ("取消"), GTK_RESPONSE_CANCEL,
        ("打开"), GTK_RESPONSE_ACCEPT,
        NULL);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *dirname = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        
        // 创建带滚动条的文字视图
        GtkWidget *scrolled = gtk_scrolled_window_new(NULL, NULL);
        GtkWidget *textview = gtk_text_view_new();
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
        
        // 读取目录内容
        DIR *dir = opendir(dirname);
        if (dir) {
            struct dirent *ent;
            while ((ent = readdir(dir)) != NULL) {
                char line[512];
                struct stat st;
                char fullpath[1024];
                snprintf(fullpath, sizeof(fullpath), "%s/%s", dirname, ent->d_name);
                
                // 获取文件信息
                if (lstat(fullpath, &st) == 0) {
                    const char *color = "#000000";
                    if (S_ISDIR(st.st_mode)) color = "#0000FF";
                    if (S_ISLNK(st.st_mode)) color = "#00FFFF";
                    
                    snprintf(line, sizeof(line),
                        "<span foreground='%s'>%-20s</span>  %8ld  %s\n",
                        color,
                        ent->d_name,
                        st.st_size,
                        ctime(&st.st_mtime));
                } else {
                    snprintf(line, sizeof(line), "%-20s\n", ent->d_name);
                }
                
                // 插入带格式的文本
                GtkTextIter iter;
                gtk_text_buffer_get_end_iter(buffer, &iter);
                gtk_text_buffer_insert_markup(buffer, &iter, line, -1);
            }
            closedir(dir);
        }
        
        // 组装界面
        gtk_container_add(GTK_CONTAINER(scrolled), textview);
        gtk_container_add(GTK_CONTAINER(window), scrolled);
        gtk_widget_show_all(scrolled);
        g_free(dirname);
    }
    gtk_widget_destroy(dialog);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "X-LS Browser");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    
    GtkWidget *button = gtk_button_new_with_label("打开目录...");
    g_signal_connect(button, "clicked", G_CALLBACK(show_directory), window);
    
    gtk_container_add(GTK_CONTAINER(window), button);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}