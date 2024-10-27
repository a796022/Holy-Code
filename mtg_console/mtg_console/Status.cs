namespace MTG
{
    public class Status
    {
        private StatusCode statusCode;
        private List<string> info;

        public Status(StatusCode statusCode, List<string> info)
        {
            this.statusCode = statusCode;
            this.info = info;
        }

        public Status(StatusCode statusCode)
        {
            this.statusCode = statusCode;
            info = new List<string>();
        }

        public StatusCode GetStatusCode()
        {
            return statusCode;
        }

        public List<string> GetInfo()
        {
            return info;
        }
    }
}