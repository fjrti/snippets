
#!/bin/bash  

# :表示必须还需要参数
# bugfix: add repo

while getopts "a:d:" opt &> /dev/null; do  
  case $opt in  
    a)  
      echo "Create repo: $OPTARG"
      curl -u 'fjrti:Kerulen1' https://api.github.com/user/repos -d '{"name":"$OPTARG", "description":""}'
      ;;  
    d)  
      echo "Delete repo: $OPTARG"   
      curl -u 'fjrti:Kerulen1' -X DELETE https://api.github.com/repos/fjrti/$OPTARG
      ;;  
    \?)  
      echo "Invalid option: -$OPTARG"   
      exit 2
      ;;  
  esac  
done  





