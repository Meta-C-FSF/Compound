#ifndef COMPOUND_FILE_H
# define COMPOUND_FILE_H

# include <Compound/string.h>

typedef enum {
  FILE_PERMISSION_NONE     = 0x000,
  FILE_PERMISSION_READ     = 0x001,
  FILE_PERMISSION_WRITE    = 0x010,
  FILE_PERMISSION_EXECUTE  = 0x100,
} FilePermission;

typedef struct _File {
  String path;
  FilePermission permission;
  bool is_dir;
  Array(struct _File *) subs;
} File;

Status File_Create(File *inst, String *path, FilePermission permission,
                   bool is_dir, Array(File) subs);

/* Copies path, permission and is_dir no matter how.
   Copies subs, if is_dir is false. */
Status File_CopyOf(File *inst, File *other);
Status File_Delete(File *inst);

Status FileUtils_FileOpen(File *inst, const char *__restrict__ mode);
Status FileUtils_FileClose(File *inst);

#endif  /* COMPOUND_FILE_H */
