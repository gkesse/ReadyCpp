GSRC = $(GPROJECT_SRC)
GBIN = $(GPROJECT_WEB)
GBUILD = build
GTARGET = $(GPROJECT_BIN)

GINCS =\
    -I$(GSRC)\include \
    
GLIBS =\

GOBJS =\
    $(patsubst $(GSRC)/%.cpp, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.cpp)) \
    $(patsubst $(GSRC)/manager/%.cpp, $(GBUILD)/%.o, $(wildcard $(GSRC)/manager/*.cpp)) \

GCFLAGS =\
    -std=gnu++11 \
    
#================================================
all: clean compile run
#================================================
# cpp
compile: $(GOBJS)
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	g++ $(GCFLAGS) -o $(GTARGET) $(GOBJS) $(GLIBS) 
$(GBUILD)/%.o: $(GSRC)/%.cpp
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	g++ $(GCFLAGS) -c $< -o $@ $(GINCS)
$(GBUILD)/%.o: $(GSRC)/manager/%.cpp
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	g++ $(GCFLAGS) -c $< -o $@ $(GINCS)
run:
	@$(GTARGET) $(argv)
clean_exe: 
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@del /s /q $(GTARGET)
clean:
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	@del /s /q $(GBUILD)\*.o $(GTARGET)
#================================================
# git
git_push:
	@cd $(GPROJECT_PATH) && git pull && git add --all && git commit -m "Initial Commit" && git push -u origin master
git_clone:
	@cd $(GPROJECT_ROOT) && git clone $(GGIT_URL) $(GGIT_NAME) 
#================================================
# batch
batch_tree:
	@tree /f $(GTREE_PATH)
#================================================
